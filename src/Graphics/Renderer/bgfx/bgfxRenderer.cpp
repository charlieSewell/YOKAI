#include "bgfxRenderer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/EventManager.hpp"
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/string_cast.hpp>
namespace
{
    static constexpr float WHITE_FURNACE_RADIANCE = 1.0f;
    
    static constexpr uint16_t ALBEDO_LUT_SIZE = 128;
    static constexpr uint16_t ALBEDO_LUT_THREADS = 16;
    float LIGHT_COUNT_VEC[4] = { static_cast<float>(1)};
    float ENV_PARAMS[] = { bx::log2(float(1024u)), 1.0f, 0.0f, 0.0f };
}
bgfxRenderer::bgfxRenderer(GLFWwindow* window) 
	: m_window(window)
{

}
int bgfxRenderer::Init()
{
    bgfx::PlatformData platformData;
    #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        platformData.nwh = ( void* )( uintptr_t )glfwGetX11Window( m_window );
        platformData.ndt = glfwGetX11Display();
    #elif BX_PLATFORM_OSX
        platformData.nwh = glfwGetCocoaWindow( m_window );
    #elif BX_PLATFORM_WINDOWS
        platformData.nwh = glfwGetWin32Window( m_window );
    #endif // BX_PLATFORM_
    bgfx::setPlatformData(platformData);
    
    bgfx::Init init;
    glfwGetWindowSize(m_window, &m_width, &m_height);
    m_oldHeight = m_height;
    m_oldWidth = m_width;
    m_reset = BGFX_RESET_VSYNC | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_MSAA_X16;
    init.resolution.width = (uint32_t)m_width;
	init.resolution.height = (uint32_t)m_height;
	init.resolution.reset = m_reset;
	
    init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;
    if(!bgfx::init(init))
    {
        return false;
    }
    m_caps = bgfx::getCaps();
    bool computeSupported = !!(m_caps->supported & BGFX_CAPS_COMPUTE);

    if (!computeSupported) {
         return false;
    }

    bgfxVertex::Init();
	PosColorTexCoord0Vertex::init();
    m_lightBuffer.init();
	// Setup ImGuis
	ImGui_Implbgfx_Init(255);
    s_texAvgLum = bgfx::createUniform("s_texAvgLum", bgfx::UniformType::Sampler);
    s_albedoLUT = bgfx::createUniform("s_texAlbedoLUT", bgfx::UniformType::Sampler);
    s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    s_prefilteredEnv = bgfx::createUniform("s_prefilterMap", bgfx::UniformType::Sampler);
    s_irradiance = bgfx::createUniform("s_irradianceMap", bgfx::UniformType::Sampler);

    u_tonemap = bgfx::createUniform("u_tonemap", bgfx::UniformType::Vec4);
    u_histogramParams = bgfx::createUniform("u_histogramparams", bgfx::UniformType::Vec4);
    m_histogramProgram = loadProgram("cs_histogram.bin", "");
    m_averagingProgram = loadProgram("cs_avglum.bin", "");
    m_albedoLUTProgram = loadProgram("cs_MS_albedoLUT.bin","");
    m_program = std::make_shared<bgfxShader>("Forward Shader","vs_shader.bin","fs_shader.bin");
    m_pbrProgram = std::make_shared<bgfxShader>("PBR Shader","vs_pbrshader.bin","fs_iblshader.bin");
    m_tonemapProgram = std::make_shared<bgfxShader>("ToneMapping Shader","vs_tonemap.bin", "fs_tonemap.bin");
    m_histogramBuffer = bgfx::createDynamicIndexBuffer(256, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);
    
    m_cubeMapFilterer = new CubeMapFilterer();
    m_lightProbe = new LightProbe{{0,2,0},512};
    t_envMap = LoadTexture("content/textures/pisa_with_mips.ktx");
    //Albedo LUT Texture
    m_albedoLUTTexture = bgfx::createTexture2D(ALBEDO_LUT_SIZE,
                                             ALBEDO_LUT_SIZE,
                                             false,
                                             1,
                                             bgfx::TextureFormat::RG16F,
                                             BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);

    GenerateAlbedoLUT();
    //FrameBuffer
    m_fbh.idx = bgfx::kInvalidHandle;
    CreateToneMapFrameBuffer();

    bgfx::setViewName(m_vHistogramPass, "Luminence Histogram");
    bgfx::setViewName(m_vAveragingPass, "Averaging the Luminence Histogram");
    bgfx::setViewName(m_vDefault, "Forward render pass");
    bgfx::setViewName(m_vToneMapPass, "Tonemapping");
    
    //Ortho projection for tonemapping
    bx::mtxOrtho(m_orthoProjection, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, m_caps->homogeneousDepth);
   
    bgfx::reset(m_width,m_height, BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4);
    bgfx::frame();

    return true;

}
void bgfxRenderer::FlushDrawQueue()
{
    for(const RENDER::DrawItem& mesh : m_drawQueue)
    {
        DrawMesh(mesh);
    }
    m_drawQueue.clear();
}
void bgfxRenderer::DrawScene(float dt)
{
    if(condition == true){
        m_lightProbe->UpdateLightProbe(m_drawQueue);
        FlushDrawQueue();
        t_filteredEnvMap = m_cubeMapFilterer->CreateFilteredCubeMap(100,m_lightProbe->GetCubeMap());
        condition = false;
    }
        
    m_caps = bgfx::getCaps();
    bgfx::setViewClear(m_vDefault, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 0x303030FF, 1.0f, 0);
    bgfx::setViewRect(m_vDefault, 0, 0, static_cast<uint16_t>(m_width), static_cast<uint16_t>(m_height));
    bgfx::setViewFrameBuffer(m_vDefault, m_fbh);
    // empty primitive in case nothing follows
    // this makes sure the clear happens
    bgfx::touch(m_vDefault);
	SetViewProjection(m_vDefault);
    
    glm::mat4 inverseview = glm::inverse(m_viewMat);
    m_viewpos = glm::vec4(inverseview[3].x, inverseview[3].y, inverseview[3].z,0.0);
    
    //Draws anything in the Draw Queue
    FlushDrawQueue();

    bgfx::setViewName(m_vToneMapPass, "Tonemap");
    bgfx::setViewRect(m_vToneMapPass, 0, 0, bgfx::BackbufferRatio::Equal);
    bgfx::setViewFrameBuffer(m_vToneMapPass, BGFX_INVALID_HANDLE);
    bgfx::setViewTransform(m_vToneMapPass, nullptr, m_orthoProjection);

    float minLogLum = -8.0f;
    float maxLogLum = 3.0f;
    float histogramParams[4] = {
        minLogLum,
        1.0f / (maxLogLum - minLogLum),
        float(m_width),
        float(m_height),
    };
    uint32_t groupsX = static_cast<uint32_t>(bx::ceil(m_width / 16.0f));
    uint32_t groupsY = static_cast<uint32_t>(bx::ceil(m_height / 16.0f));
    bgfx::setImage(0, m_fbtextures[0], 0, bgfx::Access::Read, bgfx::TextureFormat::RGBA16F);
    bgfx::setBuffer(1, m_histogramBuffer, bgfx::Access::Write);
    bgfx::setUniform(u_histogramParams, histogramParams);
    bgfx::dispatch(m_vHistogramPass, m_histogramProgram, groupsX, groupsY, 1);

    float tau = 1.1f;
    float timeCoeff = bx::clamp<float>(1.0f - bx::exp(-dt * tau), 0.0, 1.0);
    float avgParams[4] = {
        minLogLum,
        maxLogLum - minLogLum,
        timeCoeff,
        static_cast<float>(m_width * m_height),
    };
    bgfx::setImage(0, m_lumAvgTarget, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R16F);
    bgfx::setBuffer(1, m_histogramBuffer, bgfx::Access::ReadWrite);
    bgfx::setUniform(u_histogramParams, avgParams);
    bgfx::dispatch(m_vAveragingPass, m_averagingProgram, 1, 1, 1);

    bgfx::setTexture(0, s_texColor,  m_fbtextures[0], BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
    bgfx::setTexture(1, s_texAvgLum, m_lumAvgTarget, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
    screenSpaceQuad((float)m_width, (float)m_height, m_caps->originBottomLeft);
    bgfx::submit(m_vToneMapPass, m_tonemapProgram->GetRawHandle());
}
void bgfxRenderer::DeInit()
{
    if (bgfx::isValid(m_fbh))
    {
        bgfx::destroy(m_fbh);
    }
    bgfx::destroy(s_texColor);

	ImGui_Implbgfx_Shutdown();
	bgfx::shutdown();
}
void bgfxRenderer::ToggleWireFrame()
{

}

void bgfxRenderer::DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize)
{

}
void bgfxRenderer::Clear()
{

}
void bgfxRenderer::DrawGui()
{

}
void bgfxRenderer::SetDepthTesting(bool isEnabled)
{

}
void bgfxRenderer::SubmitDraw(RENDER::DrawItem drawItem)
{
    if(drawItem.shader == nullptr)
    {
        drawItem.shader = m_pbrProgram;
    } 
	m_drawQueue.push_back(drawItem);
}
const void bgfxRenderer::DrawMesh(RENDER::DrawItem mesh)
{
    bgfx::setTransform(glm::value_ptr(mesh.transform));
    glm::mat4 normalMat = glm::transpose(glm::inverse(mesh.transform));
    mesh.shader->SetUniform("u_normalMatrix", glm::value_ptr(normalMat));
    mesh.shader->SetUniform("u_lightCountVec", LIGHT_COUNT_VEC);
    mesh.shader->SetUniform("u_envParams", ENV_PARAMS);
    BindPBRMaterial(mesh.shader,mesh.mesh->GetMaterial());
    bgfx::setBuffer(Samplers::LIGHTS_POINTLIGHTS, m_lightBuffer.buffer, bgfx::Access::Read);
    
    if(mesh.camPos == glm::vec3(10000.0f,10000.0f,10000.0f)) {
        mesh.shader->SetUniform("u_camPos",glm::value_ptr(m_viewpos));
    }
    else
    {
        mesh.shader->SetUniform("u_camPos",glm::value_ptr(mesh.camPos));
    }
    if(mesh.state == 0)
    {
        mesh.state = BGFX_STATE_DEFAULT;
    }
    bgfx::setState(mesh.state);
    mesh.mesh->GetVAO()->Bind();
    bgfx::submit(mesh.viewID, mesh.shader->GetRawHandle());
}

void bgfxRenderer::UpdateLights(std::vector<PointLight> &lightsArray)
{
    m_lightBuffer.Update(lightsArray);
    //LIGHT_COUNT_VEC = lightsArray.size();
    float ambientLightIrradiance[4] = { 0.03f, 0.03f, 0.03f, 1.0f};
    m_pbrProgram->SetUniform("u_ambientLightIrradiance", ambientLightIrradiance);
}

void bgfxRenderer::ResetLightsBuffer()
{

}
void bgfxRenderer::SetViewProjection(bgfx::ViewId view)
{
    float zFar = 100.0f;
	float zNear = 0.01f;
    // view matrix
    m_viewMat = EMS::getInstance().fire(ReturnMat4Event::getViewMatrix);
    // projection matrix
    bx::mtxProj(glm::value_ptr(m_projMat),
                60.0f,
                float(m_width) / float(m_height),
                zNear,
                zFar,
                bgfx::getCaps()->homogeneousDepth,bx::Handness::Right);
                
    bgfx::setViewTransform(view, glm::value_ptr(m_viewMat), glm::value_ptr(m_projMat));
}

void bgfxRenderer::CreateToneMapFrameBuffer()
{

    uint32_t msaa = (m_reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT;

    m_fbtextures[0] =
        bgfx::createTexture2D(
                uint16_t(m_width)
                , uint16_t(m_height)
                , false
                , 1
                , bgfx::TextureFormat::RGBA16F
                , (uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT) | BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_POINT
            );
    
    const uint64_t textureFlags = BGFX_TEXTURE_RT_WRITE_ONLY | (uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT);
    bgfx::TextureFormat::Enum depthFormat;
    if (bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, textureFlags)) {
        depthFormat = bgfx::TextureFormat::D24S8;
    }
    else {
        depthFormat = bgfx::TextureFormat::D32;
    }
    m_fbtextures[1] = bgfx::createTexture2D(
        uint16_t(m_width)
        , uint16_t(m_height)
        , false
        , 1
        , depthFormat
        , textureFlags
    );

    m_fbh = bgfx::createFrameBuffer(2, m_fbtextures, true);

    if(!bgfx::isValid(m_fbh))
        SPDLOG_WARN("Failed to create tonemap framebuffer");

    bgfx::setName(m_fbh, "Render framebuffer (pre-postprocessing)");
    uint64_t lumAvgFlags = BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP;
    m_lumAvgTarget = bgfx::createTexture2D(1, 1, false, 1, bgfx::TextureFormat::R16F, lumAvgFlags);
    bgfx::setName(m_lumAvgTarget, "LumAvgTarget");
}

void bgfxRenderer::BindPBRMaterial(std::shared_ptr<bgfxShader> program,const Material &material)
{ 
    program->SetTexture("s_texBaseColor", Samplers::PBR_BASECOLOR, material.baseColorTexture);
    program->SetTexture("s_texMetallicRoughness", Samplers::PBR_METALROUGHNESS, material.metallicRoughnessTexture);
    program->SetTexture("s_texNormal", Samplers::PBR_NORMAL, material.normalTexture);
    program->SetTexture("s_texOcclusion", Samplers::PBR_OCCLUSION, material.occlusionTexture);
    program->SetTexture("s_texEmissive", Samplers::PBR_EMISSIVE, material.emissiveTexture);

    //Pack to alignment
    program->SetUniform("u_emissiveFactorVec", glm::value_ptr(material.emissiveFactor));
    program->SetUniform("u_baseColorFactor", glm::value_ptr(material.baseColorFactor));
    
    //Pack metalic factor, roughness, normal scale and occulsion strength
    float factorValues[4] = {
        material.metallicFactor, material.roughnessFactor, material.normalScale, material.occlusionStrength
    };
    program->SetUniform("u_factors", factorValues);

    BindAlbedoLUT();
}
void bgfxRenderer::GenerateAlbedoLUT()
{
    bgfx::setImage(Samplers::PBR_ALBEDO_LUT, m_albedoLUTTexture, 0, bgfx::Access::Write, bgfx::TextureFormat::RG16F);
    bgfx::dispatch(0, m_albedoLUTProgram, ALBEDO_LUT_SIZE / ALBEDO_LUT_THREADS, ALBEDO_LUT_SIZE / ALBEDO_LUT_THREADS, 1);
}

void bgfxRenderer::BindAlbedoLUT()
{
    bgfx::setTexture(Samplers::PBR_ALBEDO_LUT, s_albedoLUT, m_albedoLUTTexture);
    bgfx::setTexture(Samplers::PBR_PREFILTER_ENV_MAP, s_prefilteredEnv, t_filteredEnvMap.filteredCubeMap);
    bgfx::setTexture(Samplers::PBR_IRRADIANCE_MAP, s_irradiance, t_filteredEnvMap.irradianceMap);
}
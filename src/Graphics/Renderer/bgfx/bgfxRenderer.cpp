#include "bgfxRenderer.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/EventManager.hpp"
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
    //bgfx::renderFrame();
    bgfx::Init init;
    glfwGetWindowSize(m_window, &m_width, &m_height);
    m_oldHeight = m_height;
    m_oldWidth = m_width;
    m_reset = BGFX_RESET_VSYNC;
    init.resolution.width = (uint32_t)m_width;
	init.resolution.height = (uint32_t)m_height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	
    init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;

    if(!bgfx::init(init))
    {
        return false;
    }
    const bgfx::Caps* caps = bgfx::getCaps();
    bool computeSupported = !!(caps->supported & BGFX_CAPS_COMPUTE);

    if (!computeSupported) {
         return false;
    }

    bgfxVertex::Init();
	PosColorTexCoord0Vertex::init();
	// Setup ImGuis
	ImGui_Implbgfx_Init(255);
	//bgfx::setDebug(BGFX_DEBUG_TEXT);

    s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    s_texAvgLum = bgfx::createUniform("s_texAvgLum", bgfx::UniformType::Sampler);
    u_tonemap = bgfx::createUniform("u_tonemap", bgfx::UniformType::Vec4);
    u_histogramParams = bgfx::createUniform("u_params", bgfx::UniformType::Vec4);

    m_histogramProgram = loadProgram("cs_histogram.bin","");
    m_averagingProgram = loadProgram("cs_avglum.bin","");
    m_tonemapProgram = new bgfxShader("ToneMapping Shader","vs_tonemap.bin", "fs_tonemap.bin");
    m_program = new bgfxShader("Forward Shader","vs_shader.bin","fs_shader.bin");
    
    m_fbh.idx = bgfx::kInvalidHandle;
    m_histogramBuffer = bgfx::createDynamicIndexBuffer(256, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);

    bgfx::reset(m_width,m_height, BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4);
    CreateToneMapFrameBuffer();
    return true;

}
void bgfxRenderer::DrawScene(float dt)
{
    m_caps = bgfx::getCaps();
    if (!bgfx::isValid(m_fbh)
        || m_oldWidth != m_width
        || m_oldHeight != m_height
        || m_oldReset != m_reset)
    {
        m_reset = false;
        // Recreate variable size render targets when resolution changes.
        m_oldWidth = m_width;
        m_oldHeight = m_height;
        m_oldReset = m_reset;
        CreateToneMapFrameBuffer();
           
    }


    bgfx::setViewName(m_vDefault, "Mesh");
    bgfx::setViewClear(m_vDefault, BGFX_CLEAR_COLOR | BGFX_CLEAR_DISCARD_DEPTH | BGFX_CLEAR_DISCARD_STENCIL);
    bgfx::setViewRect(m_vDefault, 0, 0, bgfx::BackbufferRatio::Equal);
    bgfx::setViewFrameBuffer(m_vDefault, m_fbh);
    
    bgfx::setViewName(m_vHistogramPass, "Luminence Histogram");

    bgfx::setViewName(m_vAveragingPass, "Avergaing the Luminence Histogram");

    bgfx::setViewName(m_vToneMapPass, "Tonemap");
    bgfx::setViewRect(m_vToneMapPass, 0, 0, bgfx::BackbufferRatio::Equal);
    bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
    bgfx::setViewFrameBuffer(m_vToneMapPass, invalid);

    // empty primitive in case nothing follows
    // this makes sure the clear happens
    bgfx::touch(0);
	setViewProjection(m_vDefault);

    
    uint64_t state = BGFX_STATE_WRITE_RGB \
            | BGFX_STATE_WRITE_A;
    
    for(const RENDER::DrawItem& mesh : m_drawQueue)
    {
        bgfx::setTransform(glm::value_ptr(mesh.transform));
        DrawMesh(m_program,mesh.mesh,state);
    }

    
    float proj[16];
    bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.1f, 100.0f, 0.0f, m_caps->homogeneousDepth);
    bgfx::setViewTransform(m_vToneMapPass, NULL, proj);

    float minLogLum = -8.0f;
    float maxLogLum = 3.5f;
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

    float tonemap[4] = { bx::square(m_white), 0.0f, m_threshold, m_time };
    bgfx::setTexture(0, s_texColor, m_fbtextures[0]);
    bgfx::setTexture(1, s_texAvgLum, m_lumAvgTarget, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
    bgfx::setUniform(u_tonemap, tonemap);
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
    screenSpaceQuad((float)m_width, (float)m_height, m_caps->originBottomLeft);
    bgfx::submit(m_vToneMapPass, m_tonemapProgram->GetRawHandle());
	m_drawQueue.clear();
}
void bgfxRenderer::DeInit()
{
    if (bgfx::isValid(m_fbh))
    {
        bgfx::destroy(m_fbh);
    }
    delete m_tonemapProgram;
    bgfx::destroy(m_histogramProgram);
    bgfx::destroy(m_averagingProgram);
    bgfx::destroy(m_histogramBuffer);
    bgfx::destroy(m_lumAvgTarget);
    bgfx::destroy(s_texColor);
    bgfx::destroy(s_texAvgLum);
    bgfx::destroy(u_tonemap);
    bgfx::destroy(u_histogramParams);

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
	m_drawQueue.push_back(drawItem);
}
const void bgfxRenderer::DrawMesh(bgfxShader* shader, Mesh* mesh,uint64_t state)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNumber = 1;
	unsigned int heightNumber = 1;
    auto textures = mesh->getTextures();
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i].texture->Bind(i);
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        else if(name == "texture_normal")
            number = std::to_string(normalNumber++);
        else if(name == "texture_height")
            number = std::to_string(heightNumber++);
        shader->SetTexture((name + number).c_str(), static_cast<uint8_t>(i), textures[i].texture);
    }

    mesh->GetVAO()->Bind();
    //const Material& mat = scene->materials[mesh.material];
    //uint64_t materialState = pbr.bindMaterial(mat);
    state |= BGFX_STATE_BLEND_ALPHA;

    bgfx::setState(state);
    bgfx::submit(m_vDefault, m_program->GetRawHandle());

    // Reset to defaults
	for (size_t i = 0; i < textures.size(); i++) 
	{
		//textures[i].texture->UnBind(i);
	}
     
}

void bgfxRenderer::UpdateLights(std::vector<PointLight> &lightsArray)
{

}
    
void bgfxRenderer::ResetLightsBuffer()
{

}
void bgfxRenderer::setViewProjection(bgfx::ViewId view)
{
    float zFar = 300.0f;
	float zNear = 0.1f;
    // view matrix
    m_viewMat = EMS::getInstance().fire(ReturnMat4Event::getViewMatrix);
    // projection matrix
    bx::mtxProj(glm::value_ptr(m_projMat),
                60.0f,
                float(1920) / 1080,
                zNear,
                zFar,
                bgfx::getCaps()->homogeneousDepth,bx::Handness::Right);
                
    bgfx::setViewTransform(view, glm::value_ptr(m_viewMat), glm::value_ptr(m_projMat));
    bgfx::touch(0);
}

void bgfxRenderer::CreateToneMapFrameBuffer()
{
    uint32_t msaa = (m_reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT;

    if (bgfx::isValid(m_fbh))
    {
        bgfx::destroy(m_fbh);
    }

    m_fbtextures[0] = bgfx::createTexture2D(
        uint16_t(m_width)
        , uint16_t(m_height)
        , false
        , 1
        , bgfx::TextureFormat::RGBA16F
        , (uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT) | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
    );

    const uint64_t textureFlags = BGFX_TEXTURE_RT_WRITE_ONLY | (uint64_t(msaa + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT);

    bgfx::TextureFormat::Enum depthFormat =
        bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D16, textureFlags) ? bgfx::TextureFormat::D16
        : bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, textureFlags) ? bgfx::TextureFormat::D24S8
        : bgfx::TextureFormat::D32
        ;

    m_fbtextures[1] = bgfx::createTexture2D(
        uint16_t(m_width)
        , uint16_t(m_height)
        , false
        , 1
        , depthFormat
        , textureFlags
    );

    m_fbh = bgfx::createFrameBuffer(BX_COUNTOF(m_fbtextures), m_fbtextures, true);

    uint64_t lumAvgFlags = BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP;
    m_lumAvgTarget = bgfx::createTexture2D(1, 1, false, 1, bgfx::TextureFormat::R16F, lumAvgFlags);
    bgfx::setName(m_lumAvgTarget, "LumAvgTarget");
}
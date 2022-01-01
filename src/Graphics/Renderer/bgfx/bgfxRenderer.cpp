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

    s_texAvgLum = bgfx::createUniform("s_texAvgLum", bgfx::UniformType::Sampler);
    s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    u_tonemap = bgfx::createUniform("u_tonemap", bgfx::UniformType::Vec4);
    u_histogramParams = bgfx::createUniform("u_params", bgfx::UniformType::Vec4);
    
    m_histogramProgram = loadProgram("cs_histogram.bin", "");
    m_averagingProgram = loadProgram("cs_avglum.bin", "");
    m_program = new bgfxShader("Forward Shader","vs_shader.bin","fs_shader.bin");
    m_tonemapProgram = new bgfxShader("ToneMapping Shader","vs_tonemap.bin", "fs_tonemap.bin");
    
    m_histogramBuffer = bgfx::createDynamicIndexBuffer(256, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);
    

    // triangle used for blitting
    constexpr float BOTTOM = -1.0f, TOP = 3.0f, LEFT = -1.0f, RIGHT = 3.0f;
    const PosColorTexCoord0Vertex vertices[3] = { { LEFT, BOTTOM, 0.0f }, { RIGHT, BOTTOM, 0.0f }, { LEFT, TOP, 0.0f } };
    m_blitTriangleBuffer = bgfx::createVertexBuffer(bgfx::copy(&vertices, sizeof(vertices)), PosColorTexCoord0Vertex::layout);
    
    //FrameBuffer
    m_fbh.idx = bgfx::kInvalidHandle;
    CreateToneMapFrameBuffer();

    bgfx::setViewName(m_vHistogramPass, "Luminence Histogram");
    bgfx::setViewName(m_vAveragingPass, "Avergaing the Luminence Histogram");
    bgfx::setViewName(m_vDefault, "Forward render pass");
    bgfx::setViewName(m_vToneMapPass, "Tonemapping");

    bgfx::reset(m_width,m_height, BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4);
    bgfx::frame();
    return true;

}
void bgfxRenderer::DrawScene(float dt)
{
    m_caps = bgfx::getCaps();
    
    bgfx::setViewClear(m_vDefault, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030FF, 1.0f, 0);
    bgfx::setViewRect(m_vDefault, 0, 0, m_width, m_height);
    bgfx::setViewFrameBuffer(m_vDefault, m_fbh);
    // empty primitive in case nothing follows
    // this makes sure the clear happens
    bgfx::touch(0);
	setViewProjection(m_vDefault);

    uint64_t state = BGFX_STATE_DEFAULT & ~BGFX_STATE_CULL_MASK;
    
    for(const RENDER::DrawItem& mesh : m_drawQueue)
    {
        bgfx::setTransform(glm::value_ptr(mesh.transform));
        DrawMesh(m_program,mesh.mesh,state);
    }
    bgfx::discard(BGFX_DISCARD_ALL);



    m_drawQueue.clear();

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
    bgfx::setViewClear(m_vToneMapPass, BGFX_CLEAR_NONE);
    bgfx::setViewRect(m_vToneMapPass, 0, 0, m_width, m_height);
    bgfx::setViewFrameBuffer(m_vToneMapPass, BGFX_INVALID_HANDLE);
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_CULL_CW);
    bgfx::TextureHandle frameBufferTexture = bgfx::getTexture(m_fbh, 0);
    bgfx::setTexture(0, s_texColor, frameBufferTexture);
    bgfx::setTexture(1, s_texAvgLum, m_lumAvgTarget, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
    bgfx::setUniform(u_tonemap, tonemap);
    bgfx::setVertexBuffer(0, m_blitTriangleBuffer);
    bgfx::submit(m_vToneMapPass, m_tonemapProgram->GetRawHandle());

}
void bgfxRenderer::DeInit()
{
    if (bgfx::isValid(m_fbh))
    {
        bgfx::destroy(m_fbh);
    }
    delete m_tonemapProgram;
    delete m_program;
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
                float(1920) / float(1080),
                zNear,
                zFar,
                bgfx::getCaps()->homogeneousDepth,bx::Handness::Right);
                
    bgfx::setViewTransform(view, glm::value_ptr(m_viewMat), glm::value_ptr(m_projMat));
}

void bgfxRenderer::CreateToneMapFrameBuffer()
{
    const uint64_t samplerFlags = BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIP_POINT |
                                  BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP;

    bgfx::TextureFormat::Enum format = bgfx::TextureFormat::BGRA8; // BGRA is often faster (internal GPU format)
    assert(bgfx::isTextureValid(0, false, 1, format, BGFX_TEXTURE_RT | samplerFlags));
    m_fbtextures[0] =
        bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, format, BGFX_TEXTURE_RT | samplerFlags);

    bgfx::TextureFormat::Enum depthFormat = findDepthFormat(BGFX_TEXTURE_RT_WRITE_ONLY | samplerFlags,false);
    assert(depthFormat != bgfx::TextureFormat::Enum::Count);
    m_fbtextures[1] = bgfx::createTexture2D(
    bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::Enum::D32, BGFX_TEXTURE_RT_WRITE_ONLY | samplerFlags);

    m_fbh = bgfx::createFrameBuffer(2, m_fbtextures, true);

    if(!bgfx::isValid(m_fbh))
        SPDLOG_WARN("Failed to create tonemap framebuffer");

    bgfx::setName(m_fbh, "Render framebuffer (pre-postprocessing)");
    uint64_t lumAvgFlags = BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP;
    m_lumAvgTarget = bgfx::createTexture2D(1, 1, false, 1, bgfx::TextureFormat::R16F, lumAvgFlags);
    bgfx::setName(m_lumAvgTarget, "LumAvgTarget");
}
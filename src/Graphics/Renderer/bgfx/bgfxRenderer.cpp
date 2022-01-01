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
    bgfx::renderFrame();
    bgfx::Init init;
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
	
    init.resolution.width = (uint32_t)width;
	init.resolution.height = (uint32_t)height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	
    init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;

    if(!bgfx::init(init))
    {
        return false;
    }
    bgfxVertex::Init();
	
	// Setup ImGuis
	ImGui_Implbgfx_Init(255);
	//bgfx::setDebug(BGFX_DEBUG_TEXT);

    m_program = new bgfxShader("forwardShader","vs_shader.bin","fs_shader.bin");
    bgfx::reset(width,height, BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4);
    bgfx::setViewRect(m_vDefault, 0, 0, width ,height);
    bgfx::setViewName(m_vDefault, "YOKAI_ENGINE");
    bgfx::setViewClear(m_vDefault, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
   
    return true;

}
void bgfxRenderer::DrawScene(float dt)
{
    // bgfx::setViewFrameBuffer(m_vDefault, frameBuffer);

    // empty primitive in case nothing follows
    // this makes sure the clear happens
    bgfx::touch(0);
	setViewProjection(m_vDefault);
    
    uint64_t state = BGFX_STATE_WRITE_RGB \
            | BGFX_STATE_WRITE_A \
            | BGFX_STATE_WRITE_Z \
            | BGFX_STATE_DEPTH_TEST_LESS \
            | BGFX_STATE_CULL_CW \
            | BGFX_STATE_MSAA;
    
    bgfx::setState(state);
    for(const RENDER::DrawItem& mesh : m_drawQueue)
    {
        bgfx::setTransform(glm::value_ptr(mesh.transform));
        DrawMesh(m_program,mesh.mesh,state);
    }

    //bgfx::discard(BGFX_DISCARD_ALL);
	m_drawQueue.clear();
}
void bgfxRenderer::DeInit()
{
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
		textures[i].texture->UnBind(i);
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
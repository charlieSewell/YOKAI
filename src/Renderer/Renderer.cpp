#include "Renderer/Renderer.hpp"

Renderer& Renderer::getInstance()
{
    static Renderer instance;
    return instance;
}
void Renderer::Init() 
{
    try
    {
        m_renderApi = RenderAPI::Create();
    } catch (const std::exception& e) {
        std::cout << "Exception: "<<e.what() << std::endl;
    }
    m_renderApi->Init();
    registerToggleWireframe();
}

void Renderer::DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize)
{
    m_renderApi->DrawArrays(VAO,indiceSize);
}
void Renderer::DrawScene()
{
	m_renderApi->DrawScene();
}
void Renderer::DrawGui() 
{
    m_renderApi->DrawGui();
}
void Renderer::ToggleWireFrame()
{
    m_renderApi->ToggleWireFrame();
}
void Renderer::registerToggleWireframe()
{
	static bool wireFrameActive = false;

	auto toggleWireFrameReleased = [&]()
	{
		if (wireFrameActive)
			wireFrameActive = false;
	};
	EMS::getInstance().add(NoReturnEvent::toggleWireFrameReleased, toggleWireFrameReleased);

	auto toggleWireFramePressed = [&]()
	{
		if (!wireFrameActive)
		{
			m_renderApi->ToggleWireFrame();
			wireFrameActive = true;
		}
	};
	EMS::getInstance().add(NoReturnEvent::toggleWireFramePressed, toggleWireFramePressed);
}

void Renderer::Clear() 
{
    m_renderApi->Clear();
}

void Renderer::DeInit() 
{
    m_renderApi->DeInit();
}
void Renderer::SetDepthTesting(bool isEnabled)
{
    m_renderApi->SetDepthTesting(isEnabled);
}
void Renderer::UpdateLights(std::vector<PointLight> &lightsArray)
{
    m_renderApi->UpdateLights(lightsArray);
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    m_renderApi->SubmitDraw(drawItem);
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model, std::vector<glm::mat4> &finalTransforms)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    drawItem.isAnimated = true;
    drawItem.finalTransforms = finalTransforms;
    m_renderApi->SubmitDraw(drawItem);
}
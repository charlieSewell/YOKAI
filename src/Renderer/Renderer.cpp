#include "Renderer.hpp"

Renderer& Renderer::getInstance()
{
    static Renderer instance;
    return instance;
}
void Renderer::Init(GLFWwindow* window) 
{
    try
    {
        m_renderAPI = RenderAPI::Create(window);
    } catch (const std::exception& e) {
        std::cout << "Exception: "<<e.what() << std::endl;
    }
    m_renderAPI->Init();
    registerToggleWireframe();
}

void Renderer::DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize)
{
    m_renderAPI->DrawArrays(VAO,indiceSize);
}
void Renderer::DrawScene(float dt)
{
	m_renderAPI->DrawScene(dt);
}
void Renderer::DrawGui() 
{
    m_renderAPI->DrawGui();
}
void Renderer::ToggleWireFrame()
{
    m_renderAPI->ToggleWireFrame();
}
void Renderer::registerToggleWireframe()
{
	static bool wireFrameActive = false;

	auto toggleWireFrameReleased = [&]()
	{
		if (wireFrameActive)
			wireFrameActive = false;
	};
	//EMS::getInstance().add(NoReturnEvent::toggleWireFrameReleased, toggleWireFrameReleased);

	auto toggleWireFramePressed = [&]()
	{
		if (!wireFrameActive)
		{
			m_renderAPI->ToggleWireFrame();
			wireFrameActive = true;
		}
	};
	//EMS::getInstance().add(NoReturnEvent::toggleWireFramePressed, toggleWireFramePressed);
}

void Renderer::Clear() 
{
    m_renderAPI->Clear();
}

void Renderer::DeInit() 
{
    m_renderAPI->DeInit();
}
void Renderer::SetDepthTesting(bool isEnabled)
{
    m_renderAPI->SetDepthTesting(isEnabled);
}
void Renderer::UpdateLights(std::vector<PointLight> &lightsArray)
{
    m_renderAPI->UpdateLights(lightsArray);
}
void Renderer::ResetLightsBuffer()
{
    m_renderAPI->ResetLightsBuffer();
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    m_renderAPI->SubmitDraw(drawItem);
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model, std::vector<glm::mat4> &finalTransforms)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    drawItem.isAnimated = true;
    drawItem.finalTransforms = finalTransforms;
    m_renderAPI->SubmitDraw(drawItem);
}
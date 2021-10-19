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
        renderApi = RenderAPI::Create();
    } catch (const std::exception& e) {
        std::cout << "Exception: "<<e.what() << std::endl;
    }
    renderApi->Init();
    registerToggleWireframe();
}

void Renderer::DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize)
{
    renderApi->DrawArrays(VAO,indiceSize);
}
void Renderer::DrawScene()
{
	renderApi->DrawScene();
}
void Renderer::DrawGui() 
{
    renderApi->DrawGui();
}
void Renderer::ToggleWireFrame()
{
    renderApi->ToggleWireFrame();
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
			renderApi->ToggleWireFrame();
			wireFrameActive = true;
		}
	};
	EMS::getInstance().add(NoReturnEvent::toggleWireFramePressed, toggleWireFramePressed);
}

void Renderer::Clear() 
{
    renderApi->Clear();
}

void Renderer::DeInit() 
{
    renderApi->DeInit();
}
void Renderer::SetDepthTesting(bool isEnabled)
{
    renderApi->SetDepthTesting(isEnabled);
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    renderApi->SubmitDraw(drawItem);
}
void Renderer::AddToDraw(Mesh* mesh, glm::mat4 model, std::vector<glm::mat4> &finalTransforms)
{
    RENDER::DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    drawItem.isAnimated = true;
    drawItem.finalTransforms = finalTransforms;
    renderApi->SubmitDraw(drawItem);
}
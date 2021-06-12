#include "MainMenuScene.hpp"

void MainMenuScene::Init() 
{
    glfwSetInputMode(Yokai::getInstance().window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MainMenuScene::Update(float frameRate)
{
}

void MainMenuScene::Draw() 
{
    int width = 1920, height = 1080;
    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(width) / 2, static_cast<float>(height) / 2), ImGuiCond_Always, ImVec2(0.5, 0.5));
    ImGui::Begin("Main Menu"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Main Menu"); // Display some text ,you can use a format strings too
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    if (ImGui::Button("Start Game", ImVec2(500, 100))) 
    {
        std::cout << "Starting Game" << std::endl;
        Yokai::getInstance().setActiveLayer(1);
        glfwSetInputMode(Yokai::getInstance().window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (ImGui::Button("Load", ImVec2(500, 100))) 
    {
        std::cout << "Loading" << std::endl;
    }
    if (ImGui::Button("Quit", ImVec2(500, 100))) 
    {
        std::cout << "Quitting" << std::endl;
        Yokai::getInstance().setIsRunning(false);
    }
    ImGui::End();
}

void MainMenuScene::Enable() 
{
    isEnabled = true;
}

void MainMenuScene::Disable() 
{
    isEnabled = false;
}

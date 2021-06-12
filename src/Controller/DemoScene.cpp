#include "DemoScene.hpp"

void DemoScene::Init() 
{
    auto& terrainFactory = TerrainFactory::getInstance();
    terrainManager.setTerrainTexture(terrainFactory.getTextures());
    terrainManager.setGrassHeight(terrainFactory.getGrassHeight());
    terrainManager.setSandHeight(terrainFactory.getSandHeight());
    terrainManager.setSnowHeight(terrainFactory.getSnowHeight());
    terrainManager.Init();
    controlsScreen = new SplashScreen("content/Textures/help_menu.png");
    controlsScreen->setupPanel(200, 1600, 200, 800);
    controlsScreen->setActive(false);
    registerMenuButtons();

    GameObjectManager::getInstance().init();
    UIManager::getInstance().init();
    registerExit();

}

#include "Model/GameObjects/NPC.hpp"
void DemoScene::Update(float frameRate)
{
    GameObjectManager::getInstance().update(frameRate);
    UIManager::getInstance().update(frameRate);
}

void DemoScene::Draw()
{
    terrainManager.Draw(EMS::getInstance().fire(ReturnVec3Event::getPlayerPosition));
    GameObjectManager::getInstance().draw();
    UIManager::getInstance().draw();
    if (Yokai::getInstance().getIsPaused() && !UIManager::getInstance().luaGetActive("lostScreen")) 
    {
        int width = 1920, height = 1080;
        ImGui::SetNextWindowPos(ImVec2(static_cast<float>(width) / 2, static_cast<float>(height) / 2), ImGuiCond_Always, ImVec2(0.5, 0.5));
        ImGui::Begin("Pause Menu");

        ImGui::Text("Pause Menu");
        if (ImGui::Button("Resume", ImVec2(500, 100))) 
        {
            Yokai::getInstance().setIsPaused(false);
            glfwSetInputMode(Yokai::getInstance().window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        if (ImGui::Button("Save", ImVec2(500, 100))) 
        {
            std::cout << "Saving" << std::endl;
        }
        if (ImGui::Button("Quit", ImVec2(500, 100))) 
        {
            std::cout << "Quitting" << std::endl;
            Yokai::getInstance().setIsRunning(false);
        }
        ImGui::End();
    }

    if (controlsScreen->getActive()) {
        controlsScreen->draw();
    }
}
void DemoScene::Enable()
{
    isEnabled = true;
}
void DemoScene::Disable()
{
    isEnabled = false;
}

void DemoScene::registerMenuButtons() {
    static bool isPressed;
    auto menuButtonReleased = [&]() {
        isPressed = false;
    };
    EMS::getInstance().add(NoReturnEvent::toggleMenuReleased, menuButtonReleased);

    auto toggleMenuPressed = [&]() {
        if (!isPressed) {

            if (controlsScreen->getActive()) {
                glfwSetInputMode(Yokai::getInstance().window.getWindow(), GLFW_CURSOR,
                                 GLFW_CURSOR_DISABLED);
                controlsScreen->setActive(false);
                isPressed = true;
            } else {
                glfwSetInputMode(Yokai::getInstance().window.getWindow(), GLFW_CURSOR,
                                 GLFW_CURSOR_NORMAL);
                controlsScreen->setActive(true);
                isPressed = true;
            }
        }
    };
    EMS::getInstance().add(NoReturnEvent::toggleMenuPressed, toggleMenuPressed);
}

void DemoScene::registerExit() 
{
    auto exit = [&]() 
    { 
        if (Yokai::getInstance().getIsPaused() &&
            UIManager::getInstance().luaGetActive("lostScreen")) 
        {
            Yokai::getInstance().setIsRunning(false);
        }
    };

    EMS::getInstance().add(NoReturnEvent::pausePressed, exit);

}
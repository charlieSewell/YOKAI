//
// Created by charl on 2/03/2021.
//

#include "Yokai.hpp"

#include "DemoScene.hpp"
#include "MainMenuScene.hpp"
Yokai &Yokai::getInstance() 
{
    static Yokai instance;
    return instance;
}

void Yokai::Init() 
{
    if(!window.Init())
    {
        exit(0);
    }
    renderer.Init();
    if(!window.ImguiInit())
    {
        exit(0);
    }
    //Add layers to layer stack
    activeLayer = 0;
    //layers.push_back(std::shared_ptr<Layer>(new DemoScene()));
    layers.push_back(std::shared_ptr<Layer>(new MainMenuScene()));
    layers.push_back(std::shared_ptr<Layer>(new DemoScene()));
    TerrainFactory::getInstance().Init();
    PhysicsSystem::getInstance().Init();
    for(auto& layer: layers)
    {
        layer->Init();
    }

    isPaused = false;
    registerClose();
    registerClass();
}
void Yokai::Run()
{
    PhysicsSystem::getInstance().addTerrain();

    const float timeStep = 1.0f / 60;

    double lastTime = 0;
    double accumulator = 0;

    while(isRunning)
	{
		InputManagerGLFW::getInstance().processKeyboard(window.getWindow());
		InputManagerGLFW::getInstance().processGamepadButtons();

		double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        renderer.Clear();
        window.startFrame();

        if (!isPaused)
        {
			accumulator += deltaTime;
			while (accumulator >= timeStep) 
			{
				InputManagerGLFW::getInstance().processMouse(window.getWindow());
				InputManagerGLFW::getInstance().processGamepadAxis();
                PhysicsSystem::getInstance().update(timeStep);
                layers[activeLayer]->Update(static_cast<float>(timeStep));
				accumulator -= timeStep;
			}
        }
        layers[activeLayer]->Draw();

        renderer.DrawGui();
        window.endFrame();
	}
    GameObjectManager::getInstance().DeInit();
    PhysicsSystem::getInstance().DeInit();
    UIManager::getInstance().DeInit();
    renderer.DeInit();
    window.DeInit();
}

void Yokai::registerClose() {
    static bool isPressed = false;
    auto pauseRelease     = [&]() { isPressed = false; };
    EMS::getInstance().add(NoReturnEvent::pauseReleased, pauseRelease);

    auto pausePress = [&]() {
        if (!isPressed) {
            isPaused = !isPaused;
            if (isPaused) {
                glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            } else {
                glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            isPressed = true;
        }
    };
    EMS::getInstance().add(NoReturnEvent::pausePressed, pausePress);
}

void Yokai::setIsRunning(bool s) 
{
    isRunning = s;
}

std::vector<std::shared_ptr<Layer>> Yokai::getLayer() 
{
    return layers;
}

void Yokai::setActiveLayer(int a) 
{
    activeLayer = a;
}

void Yokai::setIsPaused(bool p) 
{
    isPaused = p;
}

bool Yokai::getIsPaused() const
{
    return isPaused;
}

void Yokai::registerClass() 
{
    luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
        .beginClass<Yokai>("Yokai")
        .addStaticFunction("getInstance", &Yokai::getInstance)
        .addProperty("isPaused", &Yokai::getIsPaused, &Yokai::setIsPaused)
        .endClass();
}
//
// Created by charl on 2/03/2021.
//

#include "Yokai.hpp"

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Yokai &Yokai::getInstance() 
{
    static Yokai instance;
    return instance;
}

void Yokai::Init()
{
    InitialiseLogger();
    SPDLOG_INFO("Engine Is Starting");
    if(!window.Init())
    {
        exit(0);
    }
    renderer.Init();
    modelManager = new ModelManager();
    if(!window.ImguiInit())
    {
        exit(0);
    }
    //Add layers to layer stack
    activeLayer = 0;

    try
    {
        PhysicsSystem::getInstance().Init();
        SPDLOG_INFO("Physics System Initialised");
    } catch (std::exception &e)
    {
        SPDLOG_ERROR(e.what());
    }

    for(auto& layer: layers)
    {
        layer->Init();
    }

    isPaused = false;
    registerClose();
    SPDLOG_INFO("Engine Succesfully Initialised");
}
void Yokai::Run()
{
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
    //GameObjectManager::getInstance().DeInit();
    PhysicsSystem::getInstance().DeInit();
    //UIManager::getInstance().DeInit();
    renderer.DeInit();
    window.DeInit();
}

void Yokai::registerClose()
{
    static bool isPressed = false;
    auto pauseRelease     = [&]() { isPressed = false; };
    EMS::getInstance().add(NoReturnEvent::pauseReleased, pauseRelease);

    auto pausePress = [&]()
    {
        if (!isPressed)
        {
            //TODO: Make better
            isRunning = false;
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

void Yokai::InitialiseLogger()
{
    spdlog::init_thread_pool(8192, 1);

    time_t ttime = time(nullptr);
    tm* local_time = localtime(&ttime);
    char buffer[24];
    strftime(buffer, 24, "%Y-%m-%d %H-%M-%S.txt\0", local_time);
    std::string filename = buffer;

    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/"+ filename,"Logger");
    sinks.push_back(stdout_sink);
    sinks.push_back(file_sink);

    auto log = std::make_shared<spdlog::logger>("Yokai", begin(sinks), end(sinks));

    spdlog::register_logger(log);
    spdlog::set_default_logger(log);
    spdlog::set_pattern("[%T][%s][%!][Line:%#]%^[%l]%$ %v");

}

void Yokai::addScene(std::shared_ptr<Layer> scene)
{
	layers.push_back(std::shared_ptr<Layer>(scene));
}
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

bool Yokai::Init()
{
    InitialiseLogger();
    SPDLOG_INFO("Engine Is Starting");
    if(!window.Init())
    {
        return(false);
    }
    Renderer::getInstance().Init();
    modelManager = new ModelManager();
    if(!window.ImguiInit())
    {
        return(false);
    }
    InputManagerGLFW::getInstance().AddWindow(window.getWindow());
    //Add layers to layer stack
    activeLayer = 0;

    try
    {
        PhysicsSystem::getInstance().Init();
        randomListener = new PhysicsResolution();
        PhysicsSystem::getInstance().physicsWorld->setEventListener(randomListener);
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
    registerPause();
    SPDLOG_INFO("Engine Succesfully Initialised");
    return(true);
}
void Yokai::Run()
{
    const float timeStep = 1.0f / 60;

    double lastTime = 0;
    double accumulator = 0;
    while(isRunning)
	{
		InputManagerGLFW::getInstance().processKeyboard();
		InputManagerGLFW::getInstance().processGamepadButtons();
        InputManagerGLFW::getInstance().processMouse();
		InputManagerGLFW::getInstance().processGamepadAxis();
		double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        //Renderer::getInstance().Clear();
        window.startFrame();

        if (!isPaused)
        {
			accumulator += deltaTime;
			while (accumulator >= timeStep) 
			{
                PhysicsSystem::getInstance().update(timeStep);
				accumulator -= timeStep;
			}
            layers[activeLayer]->Update(timeStep);
        }
        else 
        {
            ImGui::Begin("YOKAI DEBUG");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
            layers[activeLayer]->GetGameObjectManager()->RenderGUI();
            layers[activeLayer]->GetLightManager()->RenderGUI();
        }
        layers[activeLayer]->GetLightManager()->UpdateLights();
        layers[activeLayer]->Draw();
        PhysicsSystem::getInstance().RendererUpdate();
        Renderer::getInstance().DrawScene();
        Renderer::getInstance().DrawGui();
        window.endFrame();
	}
    PhysicsSystem::getInstance().DeInit();
    //UIManager::getInstance().DeInit();
    Renderer::getInstance().DeInit();
    window.DeInit();
}

void Yokai::Shutdown()
{
    isRunning = false;
}

std::vector<std::shared_ptr<Scene>> Yokai::getLayer()
{
    return layers;
}

void Yokai::setActiveLayer(int a) 
{
    activeLayer = a;
}

void Yokai::TogglePause() 
{
    isPaused = !isPaused;
    if(isPaused)
    {
        InputManagerGLFW::getInstance().ShowMouse();
    }
    else
    {
        InputManagerGLFW::getInstance().HideMouse();
    }
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
    spdlog::flush_on(spdlog::level::info);
    spdlog::set_pattern("[%T][%s][%!][Line:%#]%^[%l]%$ %v");

}

void Yokai::addScene(std::shared_ptr<Scene> scene)
{
	layers.push_back(std::shared_ptr<Scene>(scene));
}
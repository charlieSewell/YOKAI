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
Yokai::Yokai()
{
    if(!Init())
	{
        exit(EXIT_FAILURE);
    }
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
    isPaused = false;
    SPDLOG_INFO("Engine Succesfully Initialised");
    return(true);
}
void Yokai::Run()
{
    const float timeStep = 1.0f / 60;
    double lastTime = 0;
    double accumulator = 0;
    bool isPausePressed = false;
    InputManagerGLFW::getInstance().m_activeKeys.push_back(77);
    InputManagerGLFW::getInstance().m_activeKeys.push_back(27);
    while(isRunning)
	{
        InputManagerGLFW::getInstance().processMouse();
		InputManagerGLFW::getInstance().processGamepadAxis(); 
		InputManagerGLFW::getInstance().processKeyboard();
		InputManagerGLFW::getInstance().processGamepadButtons();
		    
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if(InputManagerGLFW::getInstance().m_keyStates[77])
        {
            if(isPausePressed == false)
            {
                isPausePressed = true;
                TogglePause();
            }
        }
        else
        {
            isPausePressed = false;
        }
        if(InputManagerGLFW::getInstance().m_keyStates[27])
        {
            Shutdown();
        }

        //Renderer::getInstance().Clear();
        window.startFrame();

        if (!isPaused)
        {
			accumulator += deltaTime;
			layers[activeLayer]->Update(deltaTime);
            while (accumulator >= timeStep) 
			{
                PhysicsSystem::getInstance().update(timeStep);
                //layers[activeLayer]->Update(timeStep);
				accumulator -= timeStep;
			}
            layers[activeLayer]->LateUpdate(deltaTime);
            
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
        PhysicsSystem::getInstance().RendererUpdate();
        layers[activeLayer]->Draw();
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
    scene->Init();
	layers.push_back(std::shared_ptr<Scene>(scene));
}
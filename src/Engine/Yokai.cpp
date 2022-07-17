//
// Created by charl on 2/03/2021.
//

#include "Yokai.hpp"
#include "JSONHelper.hpp"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "core/Time.hpp"
#include <mutex>

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
    if(!Renderer::getInstance().Init(window.GetWindow()))
    {
        return(false);
    }
    InputManagerGLFW::getInstance().AddWindow(window.GetWindow());
    
    
    m_assetSystem.AddStorage<Model>([](std::recursive_mutex &containerMutex ,std::shared_ptr<Model> &model , const std::string &fileName)
    {
        ModelLoader modelLoader;
        model = std::make_shared<Model>(modelLoader.LoadModel(fileName));
        return true;
    });

    m_activeLayer = 0;
    try
    {
        PhysicsSystem::getInstance().Init();
        m_physicsListener = new PhysicsResolution();
        PhysicsSystem::getInstance().GetPhysicsWorld()->setEventListener(m_physicsListener);
        SPDLOG_INFO("Physics System Initialised");  
    } catch (std::exception &e)
    {
        SPDLOG_ERROR(e.what());
    }
    //Initialise the first layer
    m_isPaused = false;
    SPDLOG_INFO("Engine Succesfully Initialised");
    return(true);
}
void Yokai::Run()
{
    m_layers[0]->Init();
    const float timeStep = 1.0f / 60;
    double lastTime = 0;
    double accumulator = 0;
    bool isPausePressed = false;
    bool isPhysicsPressed = false;
    InputManagerGLFW::getInstance().m_activeKeys.push_back(unsigned int(YOKAI_INPUT::GRAVE_ACCENT));
    InputManagerGLFW::getInstance().m_activeKeys.push_back(unsigned int(YOKAI_INPUT::ESCAPE));
    InputManagerGLFW::getInstance().m_activeKeys.push_back(70);
    while(m_isRunning)
	{
        InputManagerGLFW::getInstance().processMouse();
		InputManagerGLFW::getInstance().processGamepadAxis(); 
		InputManagerGLFW::getInstance().processKeyboard();
		InputManagerGLFW::getInstance().processGamepadButtons();
		    
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if(InputManagerGLFW::getInstance().m_keyStates[unsigned int(YOKAI_INPUT::GRAVE_ACCENT)])
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
        if(InputManagerGLFW::getInstance().m_keyStates[unsigned int(YOKAI_INPUT::ESCAPE)])
        {
            Shutdown();
        }

        if (InputManagerGLFW::getInstance().m_keyStates[unsigned int(YOKAI_INPUT::F)])
        {
            if (isPhysicsPressed == false) 
            {
                isPhysicsPressed = true;
                PhysicsSystem::getInstance().TogglePhysicsDebug();
            } 
        } 
        else 
        {
            isPhysicsPressed = false;
        }

        window.StartFrame(float(deltaTime));

        if (!m_isPaused)
        {
			accumulator += deltaTime;
			m_layers[m_activeLayer]->Update(deltaTime);
            while (accumulator >= timeStep) 
			{
                PhysicsSystem::getInstance().Update(timeStep);
                //layers[activeLayer]->Update(timeStep);
				accumulator -= timeStep;
			}
            m_layers[m_activeLayer]->LateUpdate(deltaTime);
        }
        else 
        {
            
            m_layers[m_activeLayer]->GetGameObjectManager()->RenderGUI();
            m_layers[m_activeLayer]->GetLightManager()->RenderGUI();
            ImGui::Begin("YOKAI Menu",NULL, ImGuiWindowFlags_MenuBar);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Select Scene");
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open..", "Ctrl+O")) { m_layers[m_activeLayer]->LoadScene();}
                    if (ImGui::MenuItem("Save", "Ctrl+S"))   { m_layers[m_activeLayer]->SaveScene();}
                    if (ImGui::MenuItem("Shutdown", "Ctrl+Q"))  { Shutdown();}
                    ImGui::EndMenu();
                }
                if(ImGui::BeginMenu("Switch Scene"))
                {
                    for(size_t i = 0; i < m_layers.size();i++)
                    {
                        if (ImGui::MenuItem(m_layers[i]->GetSceneName().c_str()))
                        {
                            SwitchScene(static_cast<unsigned int>(i));
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }        
            ImGui::End();
        }
        


        m_layers[m_activeLayer]->GetLightManager()->UpdateLights();
        PhysicsSystem::getInstance().RendererUpdate();
        m_layers[m_activeLayer]->Draw();
        Renderer::getInstance().DrawScene(float(deltaTime));
        Renderer::getInstance().DrawGui();
        window.EndFrame();
	}
    PhysicsSystem::getInstance().DeInit();
    Renderer::getInstance().DeInit();
    window.DeInit();
}

void Yokai::Shutdown()
{
    m_isRunning = false;
}

std::vector<std::shared_ptr<Scene>> Yokai::getLayer()
{
    return m_layers;
}

void Yokai::TogglePause() 
{
    m_isPaused = !m_isPaused;
    if(m_isPaused)
    {
        InputManagerGLFW::getInstance().ShowMouse();
    }
    else
    {
        InputManagerGLFW::getInstance().HideMouse();
    }
}

bool Yokai::GetIsPaused() const
{
    return m_isPaused;
}

ModelManager* Yokai::GetModelManager()
{
    return &m_modelManager;
}

void Yokai::InitialiseLogger()
{
    spdlog::init_thread_pool(8192, 1);
    std::string filename = YOKAI::time_stamp("%Y-%m-%d %H-%M-%S.txt\0");

    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/"+ filename,"Logger");
    m_sinks.push_back(stdout_sink);
    m_sinks.push_back(file_sink);

    auto log = std::make_shared<spdlog::logger>("Yokai", begin(m_sinks), end(m_sinks));

    spdlog::register_logger(log);
    spdlog::set_default_logger(log);
    spdlog::flush_on(spdlog::level::info);
    spdlog::set_pattern("[%T][%s][%!][Line:%#]%^[%l]%$ %v");

}

void Yokai::AddScene(std::shared_ptr<Scene> scene)
{
	m_layers.push_back(std::shared_ptr<Scene>(scene));
}
void Yokai::SwitchScene(unsigned int scene)
{
    if(scene < m_layers.size() && scene != m_activeLayer)
    {
        PhysicsSystem::getInstance().ClearColliders();
        m_layers[m_activeLayer]->Reset();
        m_activeLayer = scene;
        m_layers[m_activeLayer]->Init();
    }
}
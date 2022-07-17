#pragma once

#include <spdlog/spdlog.h>

#include "Engine/Scene.hpp"
#include "Model/ModelManager.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/GLFWWindow.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/PhysicsResolution.hpp"
#include "core/Resource/AssetProxy.hpp"
#include "Model/ObjectLoading/ModelLoader.hpp"
//workaround to allow vector of layer pointers
class InputComponent;
class Scene;
class PhysicsResolution;
/**
 * @class Yokai
 * @brief A class which ties together all game engine components
 */
class Yokai 
{
public:
    /**
     * @brief Returns an instance of the engine
     * @return Yokai&
     */
    static Yokai& getInstance();
    /**
     * @brief Runs the engine loop
     */
    void Run();
    ///window used by the engine
    GLFWWindow window = {};
    /**
     * @brief Shuts the engine down :(
     */
    void Shutdown();
    /**
     * @brief Gets a layer Pointer
     * @return Scene*
     */
    std::vector<std::shared_ptr<Scene>> getLayer();
    /**
     * Sets the paused state
     * @param p
     */
    void TogglePause();
    /**
     * Return true if engine paused
     * @return bool
     */
    bool GetIsPaused() const;
    /**
     * @brief Add Scene to Engine
     * @param scene 
     */
	void AddScene(std::shared_ptr<Scene> scene);
    /**
     * @brief Switch scene to scene index
     * @param scene 
     */
    void SwitchScene(unsigned int scene);
    /**
     * @brief Get the Model Manager
     * @return ModelManager* 
     */
	ModelManager* GetModelManager();
private:
    /**
     * @brief Initialises the engine
     */
    bool Init();
    //Singleton pattern requires that all constructors,destructors and copy constructors be private
    /**
     * @brief Privatised Default Constructor
     */
    Yokai();
    /**
     * @brief Privatised Default Destructor
     */
    ~Yokai() = default;
    /**
     * @brief Deleted Copy Constructor
     */
    Yokai(const Yokai&) = delete;
    /**
     * @brief Initialises the Logger
     */
    void InitialiseLogger();
    /**
     * @brief Privatised assign operator
     */
    Yokai& operator =(const Yokai&);
    ///Is engine Running
    bool m_isRunning = true;
    ///Vector of Scene layers
    std::vector<std::shared_ptr<Scene>> m_layers;
    ///is paused
    bool m_isPaused;
    ///active layer
    unsigned int m_activeLayer;
    ///Log sinks for Engine class
    std::vector<spdlog::sink_ptr> m_sinks;
    ///Model Manager
    ModelManager m_modelManager;
    ///Physics Listener
    PhysicsResolution *m_physicsListener;
    AssetProxy m_assetSystem;

    ModelLoader m_modelLoader;
};
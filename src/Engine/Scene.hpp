#pragma once
#include "Engine/JSONHelper.hpp"
#include "Engine/GameObjectManager.hpp"
#include "Engine/InputManagerGLFW.hpp"
#include "Renderer/LightManager.hpp"
#include "Yokai.hpp"

/**
 * @class Layer
 * @brief Interface of an engine layer used to control flow
 */
class Scene
{
  public:
    /**
     * @brief Initialises a Layer
     */
    virtual void Init() = 0;
    /**
     * @brief Updates a Layer Before Physics
     */
    virtual void Update(double deltaTime) = 0;
    /**
     * @brief Updates a Layer After Physics
     */
    virtual void LateUpdate(double deltaTime) = 0;
    /**
     * @brief Draw a Layer
     */
    virtual void Draw() = 0;
    /**
     * @brief Enable a Layer
     */
    virtual void Enable() = 0;
    /**
     * @brief Disable a Layer
     */
    virtual void Disable() = 0;
    /**
     * @brief Gets the Game Object Manager
     * @return GameObjectManager* 
     */
    GameObjectManager* GetGameObjectManager() {return &m_objectManager;}
    /**
     * @brief Gets the Game Light Manager
     * @return LightManager* 
     */
    LightManager* GetLightManager() {return &m_lightManager;}
    /**
     * @brief Set the Scene Name
     * @param sceneName 
     */
    void SetSceneName(std::string sceneName);
    /**
     * @brief Get the Scene Name
     * @return std::string 
     */
    std::string GetSceneName();
    /**
     * @brief Reset Scene to default state
     */
    void Reset();
    /**
     * @brief Saves Scene to file
     */
    void SaveScene();
    /**
     * @brief Loads Scene from file
     */
    void LoadScene();
  protected:
    ///Game Object Manager
    GameObjectManager m_objectManager;
    ///Lighting Manager
    LightManager m_lightManager;
    ///Name of scene
    std::string m_sceneName = "Untitled Scene";
};

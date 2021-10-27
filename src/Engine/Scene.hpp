#pragma once
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
    LightManager* GetLightManager() {return &m_lightManager;}
  protected:
    ///Game Object Manager
    GameObjectManager m_objectManager;
    LightManager m_lightManager;
};

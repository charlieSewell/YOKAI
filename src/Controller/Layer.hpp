#pragma once
#include "Controller/GameObjectManager.hpp"
#include "Controller/InputManagerGLFW.hpp"
#include "Yokai.hpp"
/**
 * @class Layer
 * @brief Interface of an engine layer used to control flow
 */
class Layer 
{
  public:
    /**
     * @brief Initialises a Layer
     */
    virtual void Init() = 0;
    /**
     * @brief Updates a Layer
     */
    virtual void Update(float frameRate) = 0;
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

  protected:
    GameObjectManager objectManager;
};

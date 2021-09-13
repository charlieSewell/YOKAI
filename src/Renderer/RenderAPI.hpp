//
// Created by Charlie Sewell on 10/03/2021.
//

#pragma once
#include "Renderer/DataTypes.hpp"
#include "Renderer/Shader.hpp"
/**
 * @class RenderAPI
 * @brief Interface for a renderAPI
 */
class RenderAPI 
{
  public:
    /**
     * @brief Destructor for RenderAPI
     */
    virtual ~RenderAPI()= default;
    /**
     * @brief Initialises the RenderAPI
     */
    virtual void Init()=0;
    /**
     * @brief Deinitialises the RenderAPI
     */
    virtual void DeInit()=0;
    /**
     * @brief Toggles Wireframe
     */
    virtual void ToggleWireFrame()=0;
    /**
     * @brief Draws a mesh to the screen
     * @param VertexArrayBuffer& - VAO
     * @param size_t - indiceSize
     */
    virtual void Draw(VertexArrayBuffer& VAO,size_t indiceSize) = 0;
    /**
     * @brief Clears the screen
     */
    virtual void Clear() =0;
    /**
     * @brief Draws GUI to screen
     */
    virtual void DrawGui() =0;
    /**
     * @brief Sets Depth Testing
     * @param bool - isEnabled
     */
    virtual void SetDepthTesting(bool isEnabled) = 0;
    /**
     * @brief Creates a specific rendering API
     * @return shared_ptr<RenderAPI> - renderAPI
     */
    static std::shared_ptr<RenderAPI> Create();
};


//
// Created by Charlie Sewell on 25/02/2021.
//
#pragma once

#include "Renderer/RenderAPI.hpp"
#include "Renderer/DataTypes.hpp"
#include "Engine/EventManager.hpp"

#include <memory>
/**
 * @class Renderer
 * @brief renders objects to the screen
 */
class Renderer 
{
  public:
    /**
     * @brief Initialises the Renderer
     */
    void Init();
    /**
     * @brief Deinitialises the renderer
     */
    void DeInit();
    /**
     * @brief Toggles Wireframe
     */
    void ToggleWireFrame();
    /**
     * @brief Draws a mesh to the screen
     * @param VertexArrayBuffer& - VAO
     * @param size_t - indiceSize
     */
    void Draw(VertexArrayBuffer& VAO,size_t indiceSize);
    /**
     * @brief Draws GUI to screen
     */
    void DrawGui();
    /**
     * @brief Clears the screen
     */
    void Clear();
    /**
     * @brief Sets Depth Testing
     * @brief bool - isEnabled
     */
    void SetDepthTesting(bool isEnabled);
  private:
    /**
     * @brief Registers button to wireframe toggle
     */
    void registerToggleWireframe();
    ///Pointer to chosen RenderAPI
    std::shared_ptr<RenderAPI> renderApi;
};


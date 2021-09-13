
#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <backends/imgui_impl_opengl3.h>
#include "Renderer/RenderAPI.hpp"
#include "Renderer/DataTypes.hpp"
#include "GLFW/glfw3.h"
#include "Engine/EventManager.hpp"
/**
 * @class OpenGLRenderer
 * @brief OpenGL rendering api implementation
 */
class OpenGLRenderer : public RenderAPI 
{
  public:
    /**
     * @brief Constructor for OpenGLRenderer
     */
    OpenGLRenderer() = default;
    /**
     * @brief Destructor for OpenGLRenderer
     */
    ~OpenGLRenderer()override = default;
    /**
     * @brief Initialises OpenGL
     */
    void Init() override;
    /**
     * @brief Deinitialises OpenGL
     */
    void DeInit() override;
    /**
     * @brief Toggles Wireframe
     */
    void ToggleWireFrame() override;
    /**
     * @brief Draws a mesh
     * @param VertexArrayBuffer& - VAO
     * @param size_t - indiceSize
     */
    void DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize) override;
    /**
     * @brief Clears the Screen after Rendering
     */
    void Clear() override;
    /**
     * @brief Draws the GUI
     */
    void DrawGui() override;
    /**
     * @param Set Depth Testing
     * @param bool - isEnabled
     */
    void SetDepthTesting(bool isEnabled) override;
    void DrawScene() override;
  private:
    ///Boolean to check whether it is in wireframe
    bool isWireFrame = false;
    Shader* shader;
};


#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "View/Renderer/RenderAPI.hpp"
#include <glm/glm.hpp>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include "View/Renderer/DataTypes.hpp"

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
    void Draw(VertexArrayBuffer& VAO,size_t indiceSize) override;
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
  private:
    ///Boolean to check whether it is in wireframe
    bool isWireFrame = false;
};

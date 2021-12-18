#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "bgfximgui.hpp"
#include "Renderer/RenderAPI.hpp"
#include "Renderer/DataTypes.hpp"

/**
 * @class bgfxRenderer
 * @brief bgfx rendering api implementation
 */
class bgfxRenderer : public RenderAPI 
{
  public:
    /**
     * @brief Constructor for bgfxRenderer
     */
    bgfxRenderer() = default;
    /**
     * @brief Destructor for bgfxRenderer
     */
    ~bgfxRenderer() = default;
    /**
     * @brief Initialises bgfx
     */
    void Init() override;
    /**
     * @brief Deinitialises bgfx
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
    void DrawScene(float dt) override;
    void SubmitDraw(RENDER::DrawItem drawItem) override; 
  private:
    void DrawMesh();
    const void DrawMesh(Shader* shader, Mesh* mesh);
};

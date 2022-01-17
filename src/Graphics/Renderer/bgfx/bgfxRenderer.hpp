#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "bgfximgui.hpp"
#include "Renderer/RenderAPI.hpp"
#include "Renderer/DataTypes.hpp"
#include "Renderer/bgfx/bgfxDataTypes.hpp"
#include "Renderer/bgfx/bgfxShader.hpp"
#include "Renderer/Samplers.hpp"
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
    bgfxRenderer(GLFWwindow* window);
    /**
     * @brief Destructor for bgfxRenderer
     */
    ~bgfxRenderer() = default;
    /**
     * @brief Initialises bgfx
     */
    int Init() override;
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
    /**
     * @brief Updates the GPU light array
     * @param lightsArray 
     */
    void UpdateLights(std::vector<PointLight> &lightsArray) override;
    /**
     * @brief Resets the GPU Lights Buffer
     */
    void ResetLightsBuffer() override;
  private:
    const void DrawMesh(bgfxShader* shader, Mesh* mesh,uint64_t state);
    void SetViewProjection(bgfx::ViewId view);
    void CreateToneMapFrameBuffer();
    void BindPBRMaterial(const Material &material);
    void GenerateAlbedoLUT();
    void BindAlbedoLUT(bool compute = false);
    GLFWwindow* m_window;
    
    glm::mat4 m_projMat {1.0};
    glm::mat4 m_viewMat {1.0};
    glm::vec3 m_viewpos {0.0};
    int m_width = 0;
    int m_height = 0;
    uint32_t m_reset = true;
    int m_oldWidth = m_width;
    int m_oldHeight = m_height;
    uint32_t m_oldReset = false;
    
    std::vector<RENDER::DrawItem> m_drawQueue;
    
    bgfxShader* m_program;
    bgfxShader* m_tonemapProgram;
    bgfxShader* m_pbrProgram;
    bgfx::ProgramHandle m_histogramProgram;
    bgfx::ProgramHandle m_averagingProgram;
    bgfx::ProgramHandle m_albedoLUTProgram;
    
    bgfx::ViewId m_vDefault = 0;
    bgfx::ViewId m_vHistogramPass = 2;
    bgfx::ViewId m_vAveragingPass = 3;
    bgfx::ViewId m_vToneMapPass = 220;

    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle s_texAvgLum;
    bgfx::UniformHandle s_albedoLUT;
    bgfx::UniformHandle u_tonemap;
    bgfx::UniformHandle u_histogramParams;

    bgfx::DynamicIndexBufferHandle m_histogramBuffer;

    bgfx::TextureHandle m_fbtextures[2];
    bgfx::TextureHandle m_lumAvgTarget;
    bgfx::TextureHandle m_albedoLUTTexture;
    bgfx::FrameBufferHandle m_fbh;

    bx::DefaultAllocator mAllocator;
    bgfx::VertexBufferHandle m_blitTriangleBuffer;
    float m_speed = 0.37f;
    float m_white = 3.0f;
    float m_threshold = 1.5f;
    float m_time = 0.0f;
    const bgfx::Caps* m_caps;

    bool m_multipleScatteringEnabled = true;
    bool m_whiteFurnaceEnabled = false;
};

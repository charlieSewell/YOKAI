#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "bgfximgui.hpp"
#include "Renderer/DataTypes.hpp"
#include "Renderer/Samplers.hpp"
#include "Renderer/RenderAPI.hpp"
#include "Renderer/bgfx/CubeMapFilterer.hpp"
#include "Renderer/bgfx/bgfxDataTypes.hpp"
#include "Renderer/bgfx/bgfxShader.hpp"
#include "Renderer/bgfx/LightBuffer.hpp"
#include "Renderer/bgfx/LightProbe.hpp"
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
    const void DrawMesh(RENDER::DrawItem mesh);
    void FlushDrawQueue();
    void SetViewProjection(bgfx::ViewId view);
    void CreateToneMapFrameBuffer();
    void BindPBRMaterial(std::shared_ptr<bgfxShader> program, const std::shared_ptr<Material> &material);
    void GenerateAlbedoLUT();
    void BindAlbedoLUT();
    GLFWwindow* m_window;
    PointLightBuffer m_lightBuffer;
    glm::mat4 m_projMat {1.0};
    glm::mat4 m_viewMat {1.0};
    glm::vec4 m_viewpos {0.0};
    int m_width = 0;
    int m_height = 0;
    uint32_t m_reset = true;
    int m_oldWidth = m_width;
    int m_oldHeight = m_height;
    uint32_t m_oldReset = false;
    
    std::vector<RENDER::DrawItem> m_drawQueue;
    
    std::shared_ptr<bgfxShader> m_program = nullptr;
    std::shared_ptr<bgfxShader> m_tonemapProgram = nullptr;
    std::shared_ptr<bgfxShader> m_pbrProgram = nullptr;
    std::shared_ptr<bgfxShader> m_skinnedProgram = nullptr;
    bgfx::ProgramHandle m_histogramProgram;
    bgfx::ProgramHandle m_averagingProgram;
    bgfx::ProgramHandle m_albedoLUTProgram;
    
    bgfx::ViewId m_vDefault = 0;
    bgfx::ViewId m_vHistogramPass = 2;
    bgfx::ViewId m_vAveragingPass = 3;
    bgfx::ViewId m_vToneMapPass = 4;

    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle s_texAvgLum;
    bgfx::UniformHandle s_albedoLUT;
    bgfx::UniformHandle s_prefilteredEnv;
    bgfx::UniformHandle s_irradiance;
    bgfx::UniformHandle u_tonemap;
    bgfx::UniformHandle u_histogramParams;
    bgfx::UniformHandle u_envParams;
    bgfx::DynamicIndexBufferHandle m_histogramBuffer;

    bgfx::TextureHandle m_fbtextures[2];
    bgfx::TextureHandle m_lumAvgTarget;
    bgfx::TextureHandle m_albedoLUTTexture;
    bgfx::FrameBufferHandle m_fbh;
    LightProbe* m_lightProbe;
    bx::DefaultAllocator mAllocator;
    float m_speed = 0.37f;
    float m_white = 3.0f;
    float m_threshold = 1.5f;
    float m_time = 0.0f;
    glm::vec4 m_lightCount;
    const bgfx::Caps* m_caps;
    bool m_multipleScatteringEnabled = true;
    bool m_whiteFurnaceEnabled = false;
    CubeMapFilterer* m_cubeMapFilterer;
    bgfx::TextureHandle t_envMap;
    FilteredCubeMap t_filteredEnvMap;
    bool condition = true;
    bool condition2 = false;
    float m_orthoProjection[16];
};

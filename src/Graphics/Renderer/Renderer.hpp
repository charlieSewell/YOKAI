//
// Created by Charlie Sewell on 25/02/2021.
//
#pragma once

#include "RenderAPI.hpp"
#include "Engine/EventManager.hpp"
#include <memory>

/**
 * @class Renderer
 * @brief renders objects to the screen
 */
class Renderer 
{
  public:
    static Renderer& getInstance();
    /**
     * @brief Initialises the Renderer
     */
    int Init(GLFWwindow* window);
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
    void DrawArrays(VertexArrayBuffer& VAO,size_t indiceSize);
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
    /**
     * @brief Adds an animated mesh to be drawn
     * @param mesh 
     * @param model 
     * @param finalTransforms 
     */
    void AddToDraw(Mesh* mesh, glm::mat4 model, std::vector<glm::mat4> &finalTransforms);
    /**
     * @brief Adds a mesh to be drawn
     * @param mesh 
     * @param model 
     */
    void AddToDraw(Mesh* mesh, glm::mat4 model);
    /**
     * @brief Flushes lights to GPU
     * @param m_lights 
     */
    void UpdateLights(std::vector<PointLight> &m_lights);
    /**
     * @brief Resets the GPU Lights buffer
     */
    void ResetLightsBuffer();
    /**
     * @brief Draws the Current Scene
     */
    void DrawScene(float dt);
  private:
    ///Default constructor for Renderer
    Renderer() = default;
    ///Default destructor for Renderer
    ~Renderer() = default;
    /**
     * @brief Registers button to wireframe toggle
     */
    void registerToggleWireframe();
    ///Pointer to chosen RenderAPI
    std::shared_ptr<RenderAPI> m_renderAPI;
};


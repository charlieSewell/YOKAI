#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
/**
 * @class Window
 * @brief Creates a window for rendering
 */
class Window {
  public:
    /**
     * @brief Default Constructor for window
     */
    Window() = default;
    /**
     * @brief Initialises the window
     * @return bool
     */
    bool Init();
    /**
     * @brief Destroys the window
     */

    void DeInit();
    /**
     * @brief Initialises ImGui
     * @return bool
     */
    bool ImguiInit();
    /**
     * @brief Returns a pointer to the window
     * @return GLFWwindow*
     */
    GLFWwindow* GetWindow();
    /**
     * @brief Starts a frame
     */
    void StartFrame();
    /**
     * @brief Ends a frame and processes callbacks
     */
    void EndFrame();
    /**
     * @brief Returns the Current Window Size
     * @return vec2 windowSize
     */
    glm::vec2 GetWindowSize();
  private:
    ///GLFW window
    GLFWwindow* m_window;
};


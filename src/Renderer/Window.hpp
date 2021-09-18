#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
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
    GLFWwindow* getWindow();
    /**
     * @brief Starts a frame
     */
    void startFrame();
    /**
     * @brief Ends a frame and processes callbacks
     */
    void endFrame();
  private:
    ///GLFW window
    GLFWwindow* window;
};


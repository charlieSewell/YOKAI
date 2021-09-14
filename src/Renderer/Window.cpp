//
// Created by charl on 6/04/2021.
//

#include "Window.hpp"
#include <spdlog/spdlog.h>
void error_callback(int error, const char* description)
{
    SPDLOG_ERROR("Error: {} {}",error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
bool Window::Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        SPDLOG_ERROR("GLFW Failed to Initialise");
        return false;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);


    window = glfwCreateWindow(1920, 1080, "YOKAI Game Engine", NULL, NULL);
    //window = glfwCreateWindow(1920, 1080, "YOKAI Game Engine", glfwGetPrimaryMonitor(), nullptr);

    if (!window)
    {
        spdlog::error("Failed to initialise the window");
        return false;
    }

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SPDLOG_INFO("Window Initialised");
    return true;
}
bool Window::ImguiInit()
{
    try{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        SPDLOG_INFO("Imgui Initialised");
        return true;
    }catch(std::exception &e)
    {
        SPDLOG_ERROR("{}",e.what());
    }
    return false;
}
void Window::DeInit()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
GLFWwindow* Window::getWindow()
{
    return window;
}
void Window::startFrame()
{
    glfwPollEvents();
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();
}
void Window::endFrame()
{
    glfwSwapBuffers(window);
}

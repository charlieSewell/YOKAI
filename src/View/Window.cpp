//
// Created by charl on 6/04/2021.
//

#include "Window.hpp"
void error_callback(int error, const char* description)
{
    std::cout << "Error:" << error << " " << description << std::endl;
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
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //window = glfwCreateWindow(1920, 1080, "ICT397 Game Engine", NULL, NULL);
    window = glfwCreateWindow(1920, 1080, "ICT397 Game Engine", glfwGetPrimaryMonitor(), nullptr);

    if (!window)
    {
        return false;
    }

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
        return true;
    }catch(std::exception &e)
    {
        std::cout << e.what() <<std::endl;
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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Window::endFrame()
{
    glfwSwapBuffers(window);
}

//
// Created by charl on 6/04/2021.
//

#include "Window.hpp"
#include <spdlog/spdlog.h>
#include "bgfx/bgfximgui.hpp"
#include "Renderer/imgui_impl_glfw.h"
void error_callback(int error, const char* description)
{
    SPDLOG_ERROR("Error: {} {}",error, description);
}
void windowSizeCallback( GLFWwindow* window, int width, int height )
{
    /*
	bigg::Application* app = ( bigg::Application* )glfwGetWindowUserPointer( window );
	app->mWidth = width;
	app->mHeight = height;
	app->reset( app->mReset );
	app->onWindowSize( width, height );
    */
}

bool Window::Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        SPDLOG_ERROR("GLFW Failed to Initialise");
        return false;
    }
    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(1920, 1080, "YOKAI Game Engine", NULL, NULL);
    //window = glfwCreateWindow(1920, 1080, "YOKAI Game Engine", glfwGetPrimaryMonitor(), nullptr);

    if (!m_window)
    {
        glfwTerminate();
        spdlog::error("Failed to initialise the window");
        return false;
    }  
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowSizeCallback( m_window, windowSizeCallback );
	ImGui::CreateContext();
    ImGui::GetIO();
	ImGui_ImplGlfw_InitForOther(m_window,true);
    SPDLOG_INFO("Window Initialised");
    return true;
}
void Window::DeInit()
{
	ImGui_ImplGlfw_Shutdown();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
GLFWwindow* Window::GetWindow()
{
    return m_window;
}
void Window::StartFrame(float dt)
{
    glfwPollEvents();
	ImGui_Implbgfx_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	
	ImGui::NewFrame();
}
void Window::EndFrame()
{
    ImGui::Render();
	ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
	bgfx::frame();
}
glm::vec2 Window::GetWindowSize()
{
    int width,height;
    glfwGetWindowSize(m_window, &width, &height);
    return glm::vec2(width,height);
}
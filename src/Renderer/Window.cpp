//
// Created by charl on 6/04/2021.
//

#include "Window.hpp"
#include <spdlog/spdlog.h>
void error_callback(int error, const char* description)
{
    SPDLOG_ERROR("Error: {} {}",error, description);
}
void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	ImGuiIO& io = ImGui::GetIO();
	if ( key >= 0 && key < IM_ARRAYSIZE( io.KeysDown ) )
	{
		if ( action == GLFW_PRESS )
		{
			io.KeysDown[ key ] = true;
		}
		else if ( action == GLFW_RELEASE )
		{
			io.KeysDown[ key ] = false;
		}
	}

	io.KeyCtrl = io.KeysDown[ GLFW_KEY_LEFT_CONTROL ] || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL ];
	io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT ] || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT ];
	io.KeyAlt = io.KeysDown[ GLFW_KEY_LEFT_ALT ] || io.KeysDown[ GLFW_KEY_RIGHT_ALT ];
	io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER ] || io.KeysDown[ GLFW_KEY_RIGHT_SUPER ];
}

void charCallback( GLFWwindow* window, unsigned int codepoint )
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddInputCharacter( codepoint );
}
void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
	ImGuiIO& io = ImGui::GetIO();
	if ( button >= 0 && button < IM_ARRAYSIZE( io.MouseDown ) )
	{
		if ( action == GLFW_PRESS )
		{
			io.MouseDown[ button ] = true;
		}
		else if ( action == GLFW_RELEASE )
		{
			io.MouseDown[ button ] = false;
		}
	}
}

void scrollCallback( GLFWwindow* window, double xoffset, double yoffset )
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += ( float )xoffset;
	io.MouseWheel += ( float )yoffset;
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

    glfwSetKeyCallback( m_window, keyCallback );
	glfwSetCharCallback( m_window, charCallback );
	glfwSetMouseButtonCallback( m_window, mouseButtonCallback );
	glfwSetScrollCallback( m_window, scrollCallback );
	glfwSetWindowSizeCallback( m_window, windowSizeCallback );

    SPDLOG_INFO("Window Initialised");
    return true;
}
void Window::DeInit()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
GLFWwindow* Window::GetWindow()
{
    return m_window;
}
void Window::StartFrame()
{
    glfwPollEvents();
}
void Window::EndFrame()
{
    //glfwSwapBuffers(m_window);
}
glm::vec2 Window::GetWindowSize()
{
    int width,height;
    glfwGetWindowSize(m_window, &width, &height);
    return glm::vec2(width,height);
}
//
// Created by charl on 1/03/2021.
//
#pragma once
#include "OpenGLRenderer.hpp"

#include "GLFW/glfw3.h"
#include "Controller/EventManager.hpp"


void OpenGLRenderer::Init() 
{
    if ((!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) )
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "Renderer Initialised: Using OpenGL" << std::endl;

}

void OpenGLRenderer::DeInit() 
{
    ImGui_ImplOpenGL3_Shutdown();
}

void OpenGLRenderer::Clear() 
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void OpenGLRenderer::ToggleWireFrame() 
{
    if(isWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isWireFrame = false;
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        isWireFrame = true;
    }
}

void OpenGLRenderer::Draw(VertexArrayBuffer& VAO, size_t indicesSize)
{
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

}
void OpenGLRenderer::DrawGui() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void OpenGLRenderer::SetDepthTesting(bool isEnabled)
{
    if(isEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
        {
        glDisable(GL_DEPTH_TEST);
    }
}
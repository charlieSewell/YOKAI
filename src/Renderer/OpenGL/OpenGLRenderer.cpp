//
// Created by charl on 1/03/2021.
//
#pragma once
#include "OpenGLRenderer.hpp"
void OpenGLRenderer::Init() 
{
    if ((!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) )
    {
        SPDLOG_ERROR("Failed to initialize GLAD");
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader = new Shader("content/Shaders/vertexShader.vert", "content/Shaders/fragmentShader.frag");
    shader->useShader();
    shader->setVec3("skyColor",glm::vec3(0.05,0.05,0.05));
    shader->setVec3("lightColor",glm::vec3(1.0,1.0,1.0));
    shader->setVec3("lightPos",glm::vec3(100, 100, 100));
    SPDLOG_INFO("Renderer Initialised: Using OpenGL");

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

void OpenGLRenderer::DrawArrays(VertexArrayBuffer& VAO, size_t indicesSize)
{
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

}
void OpenGLRenderer::DrawScene()
{
    shader->setMat4("projection",EMS::getInstance().fire(ReturnMat4Event::getPerspective));
    shader->setMat4("view",EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
    shader->setBool("isAnimated",false);
    shader->setVec3("viewPos", glm::vec3(0, 0, 0));	//TODO: Fix this later 
    auto& vector = GetDrawQueue();
    for(auto&drawItem : vector)
    {
        shader->setMat4("model",drawItem.transform);
        drawItem.drawFunction(shader);
    }
    vector.clear();
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
//
// Created by charl on 1/03/2021.
//
#pragma once
#include "OpenGLRenderer.hpp"
#include "Engine/TextureManager.hpp"
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
    shader->useShader();
    shader->setMat4("projection",EMS::getInstance().fire(ReturnMat4Event::getPerspective));
    shader->setMat4("view",EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
    shader->setBool("isAnimated",false);
    shader->setVec3("viewPos", glm::vec3(0, 0, 0));	//TODO: Fix this later 
    for(auto& drawItem : drawQueue)
    {
        shader->setMat4("model",drawItem.transform);
        DrawMesh(drawItem.mesh);
    }
    drawQueue.clear();
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
 const void OpenGLRenderer::DrawMesh(Mesh* mesh)
 {
     unsigned int diffuseNr = 1;
     unsigned int specularNr = 1;
     auto& textures = mesh->getTextures();
     for(size_t i = 0; i < textures.size(); i++)
     {
         TextureManager::getInstance().getTexture(textures[i].texture)->Bind(i);
         std::string number;
         std::string name = textures[i].type;
         if(name == "texture_diffuse")
             number = std::to_string(diffuseNr++);
         else if(name == "texture_specular")
             number = std::to_string(specularNr++);

         shader->setFloat(("material." + name + number).c_str(), static_cast<float>(i));
     }

     DrawArrays(*mesh->GetVAO(),mesh->getIndices()->size());

    // Reset to defaults
	for (size_t i = 0; i < textures.size(); i++) {
		TextureManager::getInstance().getTexture(textures[i].texture)->UnBind(i);
	}
     
}
void OpenGLRenderer::SubmitDraw(DrawItem drawItem)
{
    drawQueue.push_back(drawItem);
}
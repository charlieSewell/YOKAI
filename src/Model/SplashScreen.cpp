
#include "SplashScreen.hpp"
#include "Renderer/Renderer.hpp"
#include "Engine/TextureManager.hpp"

SplashScreen::SplashScreen(const std::string& texturePath)
{
    m_texture = TextureManager::getInstance().loadTexture(texturePath);
    m_active = true;
}

void SplashScreen::SetTexture(const std::string& texturePath)
{
    m_texture = TextureManager::getInstance().loadTexture(texturePath);
}

void SplashScreen::Draw()
{
    auto& renderer = Renderer::getInstance();
    renderer.SetDepthTesting(false);
    TextureManager::getInstance().getTexture(m_texture)->Bind(1);
    renderer.DrawArrays(*m_vao,6);
    renderer.SetDepthTesting(true);
}


void SplashScreen::SetupPanel(float left, float right, float top, float bottom) 
{
    std::vector<Vertex> verts;
    verts.resize(4);
    verts[0].position = glm::vec3(left, top, 1);
    verts[1].position = glm::vec3(right, top, 1);
    verts[2].position = glm::vec3(left, bottom, 1);
    verts[3].position = glm::vec3(right, bottom, 1);
    verts[0].textureCoords = glm::vec2(0, 0);
    verts[1].textureCoords = glm::vec2(1, 0);
    verts[2].textureCoords = glm::vec2(0, 1);
    verts[3].textureCoords = glm::vec2(1, 1);
    std::vector<unsigned int> indices = {0, 1, 2, 1, 3, 2};
    m_vao = VertexArrayBuffer::Create(verts, indices);
    verts.clear();
    indices.clear();
}

void SplashScreen::SetActive(bool a)
{
    m_active = a;
}

bool SplashScreen::GetActive() const
{
    return m_active;
}

#include "SplashScreen.hpp"
#include "Controller/Yokai.hpp"

SplashScreen::SplashScreen(const std::string& texturePath)
{
    texture = TextureManager::getInstance().loadTexture(texturePath);
    active = true;
}
void SplashScreen::setTexture(const std::string& texturePath)
{
    texture = TextureManager::getInstance().loadTexture(texturePath);
}
void SplashScreen::draw()
{
    auto& engine = Yokai::getInstance();
    engine.renderer.SetDepthTesting(false);
    TextureManager::getInstance().getTexture(texture)->Bind(1);
    engine.renderer.Draw(*vao,6);
    engine.renderer.SetDepthTesting(true);
}


void SplashScreen::setupPanel(float left, float right, float top, float bottom) 
{
    std::vector<Vertex> verts;
    verts.resize(4);
    verts[0].position = glm::vec3(left, top, 1);
    verts[1].position                 = glm::vec3(right, top, 1);
    verts[2].position                 = glm::vec3(left, bottom, 1);
    verts[3].position                 = glm::vec3(right, bottom, 1);
    verts[0].textureCoords            = glm::vec2(0, 0);
    verts[1].textureCoords            = glm::vec2(1, 0);
    verts[2].textureCoords            = glm::vec2(0, 1);
    verts[3].textureCoords            = glm::vec2(1, 1);
    std::vector<unsigned int> indices = {0, 1, 2, 1, 3, 2};
    vao                               = VertexArrayBuffer::Create(verts, indices);
    verts.clear();
    indices.clear();
}

void SplashScreen::setActive(bool a)
{
    active = a;
}

bool SplashScreen::getActive() const
{
    return active;
}
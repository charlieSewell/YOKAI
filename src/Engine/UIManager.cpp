#include "Engine/UIManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>
UIManager &UIManager::getInstance() 
{
    static UIManager instance;
    return instance;
}


void UIManager::init()
{
    splashShader = new Shader("content/Shaders/vertexShader.vert","content/Shaders/splashFragment.frag");
    splashShader->useShader();
    splashShader->setMat4("model",glm::mat4(1.0));
    splashShader->setMat4("view",glm::mat4(1.0));
    splashShader->setMat4("projection",glm::ortho(0.0f, (float)1920, (float)1080, 0.0f));
    splashShader->setInt("texture_diffuse1", 1);
    SPDLOG_INFO("UI Manger Initialised");
}

std::shared_ptr<SplashScreen> UIManager::create(const std::string& texturePath)
{
    return std::make_shared<SplashScreen>(texturePath);
}

std::string UIManager::add(std::string name, const std::string& texturePath)
{
    //uiObjects[name] = gameObject;
    uiObjects[name] = std::make_shared<SplashScreen>(texturePath);
    //std::cout << "ADD" << std::endl;
    //objectCount++;
    return name;
}

void UIManager::draw() 
{
    splashShader->useShader();
    for (auto &gameObject : uiObjects) 
    {
        if (gameObject.second->getActive()) 
        {
            gameObject.second->draw();
        }
    }
}

std::shared_ptr<SplashScreen> UIManager::getObject(const std::string& name)
{
    //std::cout << "GET" << std::endl;
    if (uiObjects[name] != nullptr) 
    {
        return uiObjects[name];
    }
    return nullptr;
}

void UIManager::DeInit() 
{
    uiObjects.clear();
}
#include "Controller/UIManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
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
    registerClass();
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

void UIManager::update(float dt) 
{
    //for (auto &gameObject : uiObjects) 
    //{
        //gameObject.second->update(dt);
    //}
    LuaManager::getInstance().runScript("content/Scripts/uiLogic.lua");
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

void UIManager::luaSetUpPanel(const std::string& name, float left, float right, float top, float bottom)
{
    getObject(name)->setupPanel(left, right, top, bottom);
}

void UIManager::luaSetTexture(const std::string& name, const std::string& texturePath)
{
    getObject(name)->setTexture(texturePath);
}

void UIManager::luaSetActive(const std::string& name, bool a)
{
    getObject(name)->setActive(a);
}

bool UIManager::luaGetActive(const std::string& name) 
{
    return getObject(name)->getActive();
}

void UIManager::registerClass() 
{
    luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
        .beginClass<UIManager>("UIManager")
        .addStaticFunction("getInstance", &UIManager::getInstance)
        .addFunction("add", &UIManager::add)
        .addFunction("getObject", &UIManager::getObject)
        .addFunction("update", &UIManager::update)
        .addFunction("setUpPanel", &UIManager::luaSetUpPanel)
        .addFunction("setTexture", &UIManager::luaSetTexture)
        .addFunction("setActive", &UIManager::luaSetActive)
        .addFunction("getActive", &UIManager::luaGetActive)
        .endClass();

    LuaManager::getInstance().runScript("content/Scripts/createUI.lua");
    
    std::cout << "UI Manager Initialised" << std::endl;
}

void UIManager::DeInit() 
{
    uiObjects.clear();
}
#include "GameObjectManager.hpp"

#include <utility>
#include <spdlog/spdlog.h>

GameObjectManager::GameObjectManager() : m_objectCount(0) {}

GameObjectManager::~GameObjectManager()
{
    m_gameObjects.clear();
}


unsigned int GameObjectManager::CreateObject()
{
    m_gameObjects.emplace(m_objectCount,std::make_shared<GameObject>(m_objectCount));
    return m_objectCount++;
}
unsigned int GameObjectManager::CreateObject(std::string objectName)
{
    m_gameObjects.emplace(m_objectCount,std::make_shared<GameObject>(m_objectCount,objectName));
    return m_objectCount++;
}


void GameObjectManager::DeleteGameObject(unsigned int id)
{
    m_gameObjects.erase(id);
}

void GameObjectManager::Update(float dt)
{
    for(auto& object : m_gameObjects)
    {
        object.second->Update(dt);
    }
}
void GameObjectManager::LateUpdate(float dt)
{
    for(auto& object : m_gameObjects)
    {
        object.second->LateUpdate(dt);
    }
}

void GameObjectManager::Draw()
{
    for(auto& object : m_gameObjects)
    {
        object.second->Draw();
    }
}

std::shared_ptr<GameObject> GameObjectManager::GetObject(unsigned int id) 
{
    if(m_gameObjects.at(id)->GetObjectID() == id)
    {
        return m_gameObjects[id];
    }
    return nullptr; 
}
void GameObjectManager::RenderGUI()
{
    ImGui::Begin("GameObject Manager");
    int selectedObject = 0;
    for(auto& object : m_gameObjects)
    {
        ImGui::PushID(object.second->GetObjectID());
        if(ImGui::TreeNode(object.second->GetName().c_str()))
        {
            object.second->RenderGUI();
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
	ImGui::End();
}
void GameObjectManager::Serialise(nlohmann::json &j)
{
    j["Objects"] = nlohmann::json::array();

    for(auto& object : m_gameObjects)
    {
        nlohmann::json temp = nlohmann::json::object();
        object.second->Serialise(temp);
        j["Objects"].push_back(temp);
    }
}
void GameObjectManager::Clear()
{
    m_gameObjects.clear();
    m_objectCount = 0;
}
#include "GameObject.hpp"
#include <iostream>
GameObject::GameObject(unsigned int id): m_gameObjectID(id){}
GameObject::GameObject(unsigned int id, std::string objectName): m_gameObjectID(id),m_objectName(objectName) {}
void GameObject::Awake()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Awake();
    }
}

void GameObject::Start()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Start();
    }
}

void GameObject::Update(float timeDelta)
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Update(timeDelta);
    }
}
void GameObject::LateUpdate(float timeDelta)
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->LateUpdate(timeDelta);
    }
}
void GameObject::Deserialise(const nlohmann::json &data)
{
    SetName(data.at("Name").get<std::string>());
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Deserialize(data);
    }
}
void GameObject::Serialise(nlohmann::json &data)
{
    data["ID"] = m_gameObjectID;
    data["Name"] = m_objectName;
    data["Components"] = nlohmann::json::array();
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Serialise(data["Components"]);
    }
}
void GameObject::Draw()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->Draw();
    }
}
unsigned int GameObject::GetObjectID()
{
    return m_gameObjectID;
}
void GameObject::RenderGUI()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->RenderGUI();
    }
}
void GameObject::SetName(std::string objectName)
{
    m_objectName = objectName;
}
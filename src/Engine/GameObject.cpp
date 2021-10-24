#include "GameObject.hpp"
#include <iostream>
GameObject::GameObject(unsigned int id): m_gameObjectID(id),m_objectName("Default Object") {}
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
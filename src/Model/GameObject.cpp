#include "GameObject.hpp"
#include <iostream>
GameObject::GameObject()
{
    static unsigned int gameObjectCounter;
    gameObjectID = gameObjectCounter++;
}
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
    return gameObjectID;
}
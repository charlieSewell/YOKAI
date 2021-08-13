#include "GameObject.hpp"

void GameObject::Awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }
}

void GameObject::Start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }
}

void GameObject::Update(float timeDelta)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Update(timeDelta);
    }
}

void GameObject::Draw()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Draw();
    }
}
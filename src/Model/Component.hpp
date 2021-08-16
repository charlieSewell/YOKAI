#pragma once

class GameObject;

class Component
{
    public:
        Component(GameObject* parent) : m_parent(parent){}
        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update(float deltaTime) {}
        virtual void Draw() {}
    protected:
        GameObject* m_parent;
};
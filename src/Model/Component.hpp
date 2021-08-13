#pragma once

class GameObject;

class Component
{
    public:
        Component(GameObject* parent) : parent(parent){}
        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update(float deltaTime) {}
        virtual void Draw() {}
    protected:
        GameObject* parent;
};
#pragma once
#include <iostream>
#include "Model/Component.hpp"
class DrawableEntity : public Component {
    public: 
        DrawableEntity(GameObject* parent);
        void Start();
        void Update(float deltaTime);
        void Draw();
        void LoadModel(std::string filename);
    private:
        unsigned int modelID;
};

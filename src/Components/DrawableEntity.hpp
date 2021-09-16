#pragma once

#include "Engine/ModelManager.hpp"
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Engine/Yokai.hpp"

class YOKAI_API DrawableEntity : public Component {
    public: 
        DrawableEntity(GameObject* parent);
        void Start();
        void Update(float deltaTime);
        void Draw();
        void LoadModel(std::string filename);
        unsigned int GetModelID(){return modelID;}
    private:
        unsigned int modelID;
};

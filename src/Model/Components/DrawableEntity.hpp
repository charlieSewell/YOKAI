#pragma once

#include "Controller/ModelManager.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
#include "Controller/Yokai.hpp"

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

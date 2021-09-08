#pragma once

#include "Controller/ModelManager.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Components/DrawableEntity.hpp"
#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
#include "Controller/Physics/PhysicsSystem.hpp"
class YOKAI_API ConcaveCollider : public Component {
    public: 
        ConcaveCollider(GameObject* parent);
        void Start();
        void Update(float deltaTime);
    private:
        unsigned int colliderID;
        unsigned int modelID;
};

#pragma once

#include "Engine/ModelManager.hpp"
#include "Transform.hpp"
#include "DrawableEntity.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
class YOKAI_API ConcaveCollider : public Component {
    public: 
        ConcaveCollider(GameObject* parent);
        void Start();
        void Update(float deltaTime);
    private:
        unsigned int colliderID;
        unsigned int modelID;
};
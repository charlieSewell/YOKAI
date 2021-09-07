#pragma once

#include "Model/Components/Transform.hpp"
#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
#include "Controller/Physics/PhysicsSystem.hpp"
class YOKAI_API SphereCollider : public Component {
public:
    SphereCollider(GameObject* parent);
    void Start();
    void Update(float deltaTime);
private:
    unsigned int colliderID;
};

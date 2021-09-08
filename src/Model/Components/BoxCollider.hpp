#pragma once
#include "Model/Components/Transform.hpp"
#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
#include "Controller/Physics/PhysicsSystem.hpp"
class YOKAI_API BoxCollider : public Component {
public:
    BoxCollider(GameObject* parent);
    void Start();
    void Update(float deltaTime);
    void SetExtents(glm::vec3 extent);
    void SetExtents(float x, float y, float z);
private:
    unsigned int colliderID;
    glm::vec3 extents;
};

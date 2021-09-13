#pragma once
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
class YOKAI_API BoxCollider : public Component {
public:
    BoxCollider(GameObject* parent);
    void Start();
    void Update(float deltaTime);
    void SetExtents(glm::vec3 extent);
    void SetExtents(float x, float y, float z);
	void SetOrientation(glm::quat orientation);
private:
    unsigned int colliderID;
    glm::vec3 extents;
};

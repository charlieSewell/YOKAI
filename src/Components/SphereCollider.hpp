#pragma once

#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
class YOKAI_API SphereCollider : public Component {
public:
    SphereCollider(GameObject* parent);
    void Start();
    void Update(float deltaTime);

	glm::vec3 NewVelocity = glm::vec3(0, 0, 0);

private:
    unsigned int colliderID;
	glm::vec3 m_lastVelocity = glm::vec3(0, 0, 0);
};

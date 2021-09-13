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

	glm::vec3 NewVelocity = glm::vec3(0, 0, 0);

private:
    unsigned int colliderID;
	glm::vec3 m_lastVelocity = glm::vec3(0, 0, 0);
};

#pragma once

#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
/**
 * @class Sphere Collider
 * @brief Sphere Collider Components
 */
class YOKAI_API SphereCollider : public Component {
public:
    /**
     * @brief Construct a new Sphere Collider object
     * @param parent 
     */
    SphereCollider(GameObject* parent);
    /**
     * @brief Starts the Collider Component
     */
    void Start();
    /**
     * @brief Updates the Collider Componet
     * @param deltaTime 
     */
    void Update(float deltaTime);
    ///New Velocity of sphere
	glm::vec3 NewVelocity = glm::vec3(0, 0, 0);

private:
    ///Collider ID
    unsigned int colliderID;
    ///Colliders Last Velocity
	glm::vec3 m_lastVelocity = glm::vec3(0, 0, 0);
};

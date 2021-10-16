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
	 * @brief Sets radius
	 * @param radius
	 */
	void SetRadius(double radius);

    /**
     * @brief Starts the Collider Component
     */
    void Start();

    ///New Velocity of sphere

	// Sets new position
	void SetPosition(glm::vec3 newPosition);

	unsigned int GetColliderID();



private:
    ///Collider ID
    unsigned int m_colliderID;
	//radius
	double m_radius = 0.05;
};

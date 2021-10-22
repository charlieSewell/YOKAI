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

    void setMass(double m);
    double getMass();

    double getInverseMass();

    void setCentreOfMass(glm::dvec3 com);
    glm::dvec3 getCentreOfMass();

    void setInertiaTensor(glm::dmat3x3 it);
    glm::dmat3x3 getInertiaTensor();

    glm::dmat3x3 getInverseInertiaTensor();

    void setLinearVelocity(glm::dvec3 lv);
    glm::dvec3 getLinearVelocity();

    void setAngularVelocity(glm::dvec3 av);
    glm::dvec3 getAngularVelocity();

    void setTorque(glm::dvec3 t);
    glm::dvec3 getTorque();

    void setForce(glm::dvec3 f);
    glm::dvec3 getForce();

    void setIsStaticObject(bool s);
    bool getIsStaticObject();

    void setGravityAffected(bool g);
    bool getGravityAffected();

	unsigned int GetColliderID();

private:
    ///Collider ID
    unsigned int m_colliderID;
	//radius
	double m_radius = 0.05;
};

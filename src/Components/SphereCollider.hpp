#pragma once

#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/ResolutionFunctions.hpp"
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
    /**
     * @brief Updates Once a frame
     * @param deltaTime
     */
    void Update(float deltaTime);

    void SetOrientation(glm::quat orientation);

    glm::quat GetOrientation();

    void SetMass(double m);
    double GetMass();

    double GetInverseMass();

    void SetCentreOfMass(glm::dvec3 com);
    glm::dvec3 GetCentreOfMass();

    void SetInertiaTensor();
    glm::dmat3x3 GetInertiaTensor();

    glm::dmat3x3 GetInverseInertiaTensor();

    void SetLinearVelocity(glm::dvec3 lv);
    glm::dvec3 GetLinearVelocity();

    void SetAngularVelocity(glm::dvec3 av);
    glm::dvec3 GetAngularVelocity();

    void SetIsStaticObject(bool s);
    bool GetIsStaticObject();

    void SetGravityAffected(bool g);
    bool GetGravityAffected();

    double GetRadius();

    /**
     * @brief Set the Position of the Sphere
     * @param orientation
     */
    void SetPosition(glm::dvec3 newPosition);

    glm::dvec3 GetPosition();

    int GetColliderID();

    void Translate(glm::dvec3 position);

    void Rotate(glm::dvec3 angVelocity, float deltaTime);

private:
    ///Collider ID
    unsigned int m_colliderID;
	//radius
	double m_radius = 0.05;
};

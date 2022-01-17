#pragma once

#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/ResolutionFunctions.hpp"
/**
 * @class Sphere Collider
 * @brief Sphere Collider Components
 */
class SphereCollider : public Component {
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
	void SetRadius(float radius);

    /**
     * @brief Starts the Collider Component
     */
    void Start();
    /**
     * @brief Updates Once a frame
     * @param deltaTime
     */
    void Update(float deltaTime);
    /**
     * @brief Updates Sphere collider
     * @param deltaTime 
     */
    void LateUpdate(float deltaTime);
    /**
     * @brief Updates the Phsyics on sphere collider
     * @param deltaTime 
     */
    void PhysicsUpdate(float deltaTime);
    /**
     * @brief Set the Orientation of the sphere
     * @param orientation 
     */
    void SetOrientation(glm::quat orientation);
    /**
     * @brief Get the Orientation of the sphere
     * @return glm::quat 
     */
    glm::quat GetOrientation();
    /**
     * @brief Set the Mass
     * @param m 
     */
    void SetMass(float m);
    /**
     * @brief Get the Mass
     * @return double 
     */
    float GetMass();
    /**
     * @brief Get the Inverse Mass
     * @return double 
     */
    float GetInverseMass();
    /**
     * @brief Set the Centre Of Mass
     * @param com 
     */
    void SetCentreOfMass(glm::vec3 com);
    /**
     * @brief Get the Centre Of Mass
     * @return glm::dvec3 
     */
    glm::vec3 GetCentreOfMass();
    /**
     * @brief Initialize the inertia tensor
     */
    void SetInertiaTensor();
    /**
     * @brief Get the Inertia Tensor
     * @return glm::dmat3x3 
     */
    glm::mat3x3 GetInertiaTensor();
    /**
     * @brief Get the Inverse Inertia Tensor
     * @return glm::dmat3x3 
     */
    glm::mat3x3 GetInverseInertiaTensor();
    /**
     * @brief Set the Linear Velocity
     * @param lv 
     */
    void SetLinearVelocity(glm::vec3 lv);
    /**
     * @brief Get the Linear Velocity
     * @return glm::dvec3 
     */
    glm::vec3 GetLinearVelocity();
    /**
     * @brief Set the Angular Velocity
     * @param av 
     */
    void SetAngularVelocity(glm::vec3 av);
    /**
     * @brief Get the Angular Velocity
     * @return glm::dvec3 
     */
    glm::vec3 GetAngularVelocity();
    /**
     * @brief Set Is Static Object
     * @param s 
     */
    void SetIsStaticObject(bool s);
    /**
     * @brief Get Is Static Object
     * @return bool
     */
    bool GetIsStaticObject();
    /**
     * @brief Set is Gravity Affected
     * @param g 
     */
    void SetGravityAffected(bool g);
    /**
     * @brief Get is Gravity Affected
     * @param g 
     */
    bool GetGravityAffected();
    /**
     * @brief Get the Radius
     * @return double 
     */
    float GetRadius();
    /**
     * @brief Set the Position of the Sphere
     * @param glm::vec3
     */
    void SetPosition(glm::vec3 newPosition);
    /**
     * @brief Get the Position 
     * 
     * @return glm::vec3 
     */
    glm::vec3 GetPosition();
    /**
     * @brief Get the Collider ID
     * @return int 
     */
    unsigned int GetColliderID();
    /**
     * @brief Translate the ball along a heading
     * @param position 
     */
    void Translate(glm::vec3 position);
    /**
     * @brief Initialise static object
     */
    void StaticSet();
    /**
     * @brief Rotates an object along a heading
     * @param angVelocity 
     * @param deltaTime 
     */
    void Rotate(glm::vec3 angVelocity, float deltaTime);
    /**
     * @brief Set the Collision Category
     * @param category 
     */
    void SetCollisionCategory(unsigned short category);
    /**
     * @brief Set the Collision Mask Bits
     * @param maskBits 
     */
    void SetCollisionMaskBits(unsigned short maskBits);

private:
    ///Collider ID
    unsigned int m_colliderID;
	//radius
	float m_radius = 0.05f;
};

#pragma once
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/CollisionBody.hpp"
#include "Physics/ResolutionFunctions.hpp"
/**
 * @class BoxCollider
 * @brief Box collider component
 */
class BoxCollider : public Component {
public:
    /**
     * @brief Construct a new Box Collider object
     * @param parent 
     */
    BoxCollider(GameObject* parent);
    /**
     * @brief Runs once when the scene is ready to go
     */
    void Start();
    /**
     * @brief Updates Before the Physics Simulation
     * @param deltaTime 
     */
    void Update(float deltaTime);
    /**
     * @brief Updates After the Physics Simulation
     * @param deltaTime 
     */
    void LateUpdate(float deltaTime);
    /**
     * @brief Renders the GUI for this boxcollider
     */
    void RenderGUI();
    /**
     * @brief Set the Extents of the Bounding Box
     * @param extent 
     */
    void SetExtents(glm::vec3 extent);
    /**
     * @brief Set the Extents of the Bounding Box
     * @param x 
     * @param y 
     * @param z 
     */
    void SetExtents(float x, float y, float z);
    /**
     * @brief Set the Orientation of the Bounding Box
     * @param orientation 
     */
	void SetOrientation(glm::quat orientation);
    /**
     * @brief Get the Orientation
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
     * @return glm::vec3 
     */
    glm::vec3 GetCentreOfMass();
    /**
     * @brief Initializes the inertia tensor
     */
    void SetInertiaTensor();
    /**
     * @brief Get the Inertia Tensor
     * @return glm::mat3x3 
     */
    glm::mat3x3 GetInertiaTensor();
    /**
     * @brief Get the Inverse Inertia Tensor
     * 
     * @return glm::mat3x3 
     */
    glm::mat3x3 GetInverseInertiaTensor();
    /**
     * @brief Set the Linear Velocity
     * @param lv 
     */
    void SetLinearVelocity(glm::vec3 lv);
    /**
     * @brief Get the Linear Velocity
     * @return glm::vec3 
     */
    glm::vec3 GetLinearVelocity();
    /**
     * @brief Set the Angular Velocity
     * @param av 
     */
    void SetAngularVelocity(glm::vec3 av);
    /**
     * @brief Get the Angular Velocity
     * @return glm::vec3 
     */
    glm::vec3 GetAngularVelocity();
    /**
     * @brief Is this object static
     * @param s 
     */
    void SetIsStaticObject(bool s);
    /**
     * @brief Get the Is Static Object object
     * @return bool
     */
    bool GetIsStaticObject();
    /**
     * @brief Sets Whether Object is gravity affected
     * @param g 
     */
    void SetGravityAffected(bool g);
    /**
     * @brief Gets Whether Object is gravity affected
     * @return bool
     */
    bool GetGravityAffected();
    /**
     * @brief Get the Extents
     * @return glm::dvec3 
     */
    glm::dvec3 GetExtents();
	/**
	* @brief Set the Positin of the Bounding Box
	* @param orientation
	*/
	void SetPosition(glm::vec3 newPosition);
    /**
     * @brief Get the Position of the Bounding Box
     * @return glm::vec3 
     */
    glm::vec3 GetPosition();
    /**
     * @brief Get the Collider ID
     * @return int 
     */
	unsigned int GetColliderID();
    /**
     * @brief Translate the collider along a heading
     * @param velocity 
     */
    void Translate(glm::vec3 velocity);
    /**
     * @brief Rotates the collider along a heading
     * @param angVelocity 
     * @param deltaTime 
     */
    void Rotate(glm::vec3 angVelocity, float deltaTime);
    /**
     * @brief Initialises a static object
     */
    void StaticSet();
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
    ///Extents of Bounding Box
    glm::vec3 extents = {};
    //Offset in position from Transform
    glm::vec3 m_offset = {};
};

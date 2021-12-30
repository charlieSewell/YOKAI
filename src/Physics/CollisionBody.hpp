#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "Shapes/ReactTerrainShape.hpp"
#include "Physics.hpp"
#include "ReactMath.hpp"
//#include "PhysicsResolution.hpp"

/**
 * @class CollisionBody
 * @brief Class for a physics Rigid body
 */
class CollisionBody 
{
  public:
    /**
     * @brief Sets Position
     * @param vec3 -position
     */
    void SetPosition(glm::vec3 position);
    /**
     * @brief Sets Orientation
     * @param quat - orientation
     */
    void SetOrientation(glm::quat orientation);
    /**
     * @brief Creates the physics body
     * @param gameObjID
     * @param physicsWorld
     * @param position
     * @param orientation
     */
    void CreateBody(int gameObjID, rp3d::PhysicsWorld *physicsWorld, glm::vec3 position,
                    glm::quat orientation);
    /**
     * @brief Deletes the physics body
     * @param physicsWorld
     * @param physicsCommon
     */
    void DeleteBody(rp3d::PhysicsWorld *physicsWorld, rp3d::PhysicsCommon &physicsCommon);
    /**
     * @brief Gets position
     * @return vec3
     */
    glm::vec3 GetPosition();
    /**
     * @brief Gets Orientation
     * @return quat
     */
    glm::quat GetOrientation();
    /**
     * @brief Returns the rp3d Rigidbody
     * @return RigidBody*
     */
    reactphysics3d::CollisionBody *GetCollisionBody() {return m_body;}
    /**
     * @brief Adds a collision Shape
     * @param shape
     */
    void AddCollisionShape(ReactShape *shape);

    /**
     * @brief Sets the friction on the body
     * @param friction
     */
    void SetFrictionCoefficient(float friction);
    /**
     * @brief Sets the rolling Resistance
     * @param resistance
     */
    void SetRollingResistance(float resistance);

    /**
     * @brief Returns the ColliderID
     * @return ID
     */
    uint32_t GetColliderID() {
        return m_collider->getEntity().id;
    }
    /**
     * @brief Returns the owning game objects ID
     * @return
     */
    [[nodiscard]] int GetGameObjectID() const {
        return m_gameObjectID;
    }
    /**
     * @brief Set the Mass
     * @param m 
     */
    void SetMass(float m);
    /**
     * @brief Get the Mass
     * @return float 
     */
    float GetMass();
    /**
     * @brief Get the Inverse Mass
     * @return float 
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
     * @brief Set the Inertia Tensor
     * @param it 
     */
    void SetInertiaTensor(glm::mat3x3 it);
    /**
     * @brief Get the Inertia Tensor
     * @return glm::mat3x3 
     */
    glm::mat3x3 GetInertiaTensor();
    /**
     * @brief Get the Inverse Inertia Tensor
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
     * @brief Set the body static
     * @param s 
     */
    void SetIsStaticObject(bool s);
    /**
     * @brief Get is the body static
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
     * @return bool 
     */
    bool GetGravityAffected();
    /**
     * @brief Set the Force
     * @param f 
     */
    void SetForce(glm::vec3 f);
    /**
     * @brief Gets the Force
     * @return glm::vec3 
     */
    glm::vec3 GetForce();
    /**
     * @brief Set the Collision Category 
     * @param category 
     */
    void SetCollisionCategory(unsigned short category);
    /**
     * @brief Set the Collision Mask Bits
     * 
     * @param maskBits 
     */
    void SetCollisionMaskBits(unsigned short maskBits);

	bool m_hasCollided = false;
	int m_counter = 0;
    glm::mat4 GetTransform();
    void UpdateBody();

  private:
    /// Shape of collider
    ReactShape *m_shape;
    /// Owning game object ID
    int m_gameObjectID = -1;
    /// React Rigid Body
    reactphysics3d::CollisionBody *m_body;
    /// React Collider
    reactphysics3d::Collider *m_collider;
    ///Collider Position
    glm::vec3 m_position = {};
    ///Center of mass of Collider
    glm::vec3 m_centreOfMass           = {};
    ///Interia Tensor of Collider
    glm::mat3x3 m_inertiaTensor        = {};
    ///Inverse Interia Tensor of Collider
    glm::mat3x3 m_inverseInertiaTensor = {};
    ///Linear velocity of collider
    glm::vec3 m_linearVelocity  = {};
    ///Angular Velocity of Collider
    glm::vec3 m_angularVelocity = {};
    ///Orientation of Collider
    glm::quat m_orientation     = {};
    ///Mass of Collider
    float m_mass;
    ///Inverse mass of Collider
    float m_inverseMass;
    ///Is Collider Static
    bool m_staticObject;
    ///Is Collider Gravity affected
    bool m_gravityAffected;
};

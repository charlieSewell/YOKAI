#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "Physics/Shapes/ReactTerrainShape.hpp"
#include "PhysicsUnits.hpp"
//#include "PhysicsResolution.hpp"
#include "ReactMath.hpp"
/**
 * @class RigidBody
 * @brief Class for a physics Rigid body
 */
class CollisionBody {

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
    reactphysics3d::CollisionBody *getCollisionBody() {
        return m_body;
    }
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
    uint32_t getColliderID() {
        return m_collider->getEntity().id;
    }
    /**
     * @brief Returns the owning game objects ID
     * @return
     */
    [[nodiscard]] int getGameObjectID() const {
        return gameObjectID;
    }

    void SetMass(float m);
    float GetMass();

    float GetInverseMass();

    void SetCentreOfMass(glm::vec3 com);
    glm::vec3 GetCentreOfMass();

    void SetInertiaTensor(glm::mat3x3 it);
    glm::mat3x3 GetInertiaTensor();

    glm::mat3x3 GetInverseInertiaTensor();

    void SetLinearVelocity(glm::vec3 lv);
    glm::vec3 GetLinearVelocity();

    void SetAngularVelocity(glm::vec3 av);
    glm::vec3 GetAngularVelocity();

    void SetIsStaticObject(bool s);
    bool GetIsStaticObject();

    void SetGravityAffected(bool g);
    bool GetGravityAffected();

    glm::mat4 GetTransform();
    void UpdateBody();

  private:
    /// Shape of collider
    ReactShape *shape;
    /// Owning game object ID
    int gameObjectID = -1;
    /// React Rigid Body
    reactphysics3d::CollisionBody *m_body;
    /// React Collider
    reactphysics3d::Collider *m_collider;

    // PHYSICS
    float m_mass;
    float m_inverseMass;
    glm::vec3 m_centreOfMass           = {};
    glm::mat3x3 m_inertiaTensor        = {};
    glm::mat3x3 m_inverseInertiaTensor = {};

    glm::vec3 m_linearVelocity  = {};
    glm::vec3 m_angularVelocity = {};
    glm::quat m_orientation     = {};
    bool m_staticObject;
    bool m_gravityAffected;

    glm::vec3 m_position = {};
    glm::vec3 m_tempLinearVelocity = {};
};

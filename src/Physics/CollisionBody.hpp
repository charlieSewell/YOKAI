#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "Physics/Shapes/ReactTerrainShape.hpp"
#include "PhysicsUnits.hpp"
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
    void CreateBody(int gameObjID,rp3d::PhysicsWorld* physicsWorld,glm::vec3 position,glm::quat orientation);
    /**
     * @brief Deletes the physics body
     * @param physicsWorld
     * @param physicsCommon
     */
    void DeleteBody(rp3d::PhysicsWorld* physicsWorld,rp3d::PhysicsCommon &physicsCommon);
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
    reactphysics3d::CollisionBody* getCollisionBody(){return m_body;}
    /**
     * @brief Adds a collision Shape
     * @param shape
     */
    void AddCollisionShape(ReactShape* shape);

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
    uint32_t getColliderID(){return m_collider->getEntity().id;}
    /**
     * @brief Returns the owning game objects ID
     * @return
     */
    [[nodiscard]] int getGameObjectID() const{return gameObjectID;}

private:
    ///Shape of collider
    ReactShape* shape;
    ///Owning game object ID
    int gameObjectID = -1;
    ///React Rigid Body
    reactphysics3d::CollisionBody* m_body;
    ///React Collider
    reactphysics3d::Collider* m_collider;

    //PHYSICS
    double mass;
    double inverseMass;
    glm::dvec3 centreOfMass;
    glm::dmat3x3 inertiaTensor;
    glm::dmat3x3 inverseInertiaTensor;

    glm::dvec3 linearVelocity;
    glm::dvec3 angularVelocity;
    glm::dvec3 torque;
    glm::dvec3 force;

    bool staticObject;

};

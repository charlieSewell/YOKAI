//
// Created by charl on 19/05/2021.
//
#pragma once
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include "Controller/Physics/Shapes/ReactTerrainShape.hpp"
/**
 * @class RigidBody
 * @brief Class for a physics Rigid body
 */
class RigidBody {

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
     * @brief Applys a force to the body
     * @param force
     */
    void ApplyForceToCentre(glm::vec3 force);
    /**
     * @brief Returns the rp3d Rigidbody
     * @return RigidBody*
     */
    reactphysics3d::RigidBody* getRigidBody(){return body;}
    /**
     * @brief Adds a collision Shape
     * @param shape
     */
    void AddCollisionShape(ReactShape* shape);
    /**
     * @brief Sets the body Type
     * @param type
     */
    void SetBodyType(rp3d::BodyType type);
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
     * @brief Sets the linear velocity
     * @param velocity
     */
    void SetLinearVelocity(glm::vec3 velocity);
    /**
     * @brief Sets the angular velocity
     * @param velocity
     */
    void SetAngularVelocity(glm::vec3 velocity);
    /**
     * @brief Sets the angular damping
     * @param damping
     */
    void SetAngularDamping(double damping);
    /**
     * @brief Sets the linear damping
     * @param damping
     */
    void SetLinearDamping(double damping);
    /**
     * @brief Gets Linear Velocity
     * @return vec3
     */
    glm::vec3 GetLinearVelocity();
    /**
     * @brief Gets Angular Velocity
     * @return vec3
     */
    glm::vec3 GetAngularVelocity();
    /**
     * @brief Sets the Bounciness
     * @param bounciness
     */
    void SetBounciness(float bounciness);
    /**
     * @brief Sets the Mass
     * @param mass
     */
    void SetMass(float mass);
    /**
     * @brief Sets the Sleep State
     * @param sleepState
     */
    void SetIsAllowedToSleep(bool sleepState);
    /**
     * @brief Returns the ColliderID
     * @return ID
     */
    uint32_t getColliderID(){return collider->getEntity().id;}
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
    reactphysics3d::RigidBody* body;
    ///React Collider
    reactphysics3d::Collider* collider;



};

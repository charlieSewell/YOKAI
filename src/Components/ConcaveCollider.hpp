#pragma once

#include "Model/ModelManager.hpp"
#include "Transform.hpp"
#include "DrawableEntity.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include "Physics/PhysicsSystem.hpp"
/**
 * @class ConcaveCollider
 * @brief A concave bounding volume 
 */
class ConcaveCollider : public Component {
    public: 
        /**
         * @brief Construct a new Concave Collider object
         * @param parent 
         */
        ConcaveCollider(GameObject* parent);
        /**
         * @brief Runs once when scene is ready to go
         */
        void Start();
        /**
         * @brief Runs once a frame to update object
         * @param deltaTime 
         */
        void Update(float deltaTime);
        /**
         * @brief Set the Mass
         * @param m 
         */
        void setMass(float m);
        /**
         * @brief Get the Mass
         * @return double 
         */
        float getMass();
        /**
         * @brief Get the Inverse Mass
         * @return double 
         */
        float getInverseMass();
        /**
         * @brief Set the Centre Of Mass
         * @param com 
         */
        void setCentreOfMass(glm::vec3 com);
        /**
         * @brief Get the Centre Of Mass
         * @return glm::dvec3 
         */
        glm::vec3 getCentreOfMass();
        /**
         * @brief Set the Inertia Tensor
         * @param it 
         */
        void setInertiaTensor(glm::mat3x3 it);
        /**
         * @brief Get the Inertia Tensor
         * @return glm::dmat3x3 
         */
        glm::mat3x3 getInertiaTensor();
        /**
         * @brief Get the Inverse Inertia Tensor
         * @return glm::dmat3x3 
         */
        glm::mat3x3 getInverseInertiaTensor();
        /**
         * @brief Set the Linear Velocity
         * @param lv 
         */
        void setLinearVelocity(glm::vec3 lv);
        /**
         * @brief Get the Linear Velocity
         * @return glm::dvec3 
         */
        glm::vec3 getLinearVelocity();
        /**
         * @brief Set the Angular Velocity
         * @param av 
         */
        void setAngularVelocity(glm::vec3 av);
        /**
         * @brief Get the Angular Velocity
         * @return glm::dvec3 
         */
        glm::vec3 getAngularVelocity();
        /**
         * @brief Set Is Static Object
         * @param s 
         */
        void setIsStaticObject(bool s);
        /**
         * @brief Get Is Static Object
         * @return bool
         */
        bool getIsStaticObject();
        /**
         * @brief Set is Gravity Affected
         * @param g 
         */
        void setGravityAffected(bool g);
        /**
         * @brief Get is Gravity Affected
         * @return bool
         */
        bool getGravityAffected();

    private:
        ///Collider ID
        unsigned int m_colliderID;
        ///Model ID
        unsigned int modelID;
};
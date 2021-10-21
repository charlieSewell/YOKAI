#pragma once

#include "Engine/ModelManager.hpp"
#include "Transform.hpp"
#include "DrawableEntity.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
/**
 * @class ConcaveCollider
 * @brief A concave bounding volume 
 */
class YOKAI_API ConcaveCollider : public Component {
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

    private:
        ///Collider ID
        unsigned int m_colliderID;
        ///Model ID
        unsigned int modelID;

        //unsigned int m_colliderID;
};
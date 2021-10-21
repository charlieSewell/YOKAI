#pragma once
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Physics/CollisionBody.hpp"
#include "Physics/ResolutionFunctions.hpp"
/**
 * @class BoxCollider
 * @brief Box collider component
 */
class YOKAI_API BoxCollider : public Component {
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
     * @brief Updates Once a frame
     * @param deltaTime 
     */
    void Update(float deltaTime);
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

    void SetPosition(glm::vec3 newPosition);

    void setMass(double m);
    double getMass();

    double getInverseMass();

    void setCentreOfMass(glm::dvec3 com);
    glm::dvec3 getCentreOfMass();

    void setInertiaTensor();
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

    glm::vec3 getExtents();

    void initInertiaTensor();

private:
    ///Collider ID
    unsigned int colliderID;
    ///Extents of Bounding Box
    glm::vec3 extents;
};

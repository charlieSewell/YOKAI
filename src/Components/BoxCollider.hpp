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

    void SetTorque(glm::dvec3 t);
    glm::dvec3 GetTorque();

    void SetForce(glm::dvec3 f);
    glm::dvec3 GetForce();

    void SetIsStaticObject(bool s);
    bool GetIsStaticObject();

    void SetGravityAffected(bool g);
    bool GetGravityAffected();

    glm::dvec3 GetExtents();

	/**
	* @brief Set the Positin of the Bounding Box
	* @param orientation
	*/
	void SetPosition(glm::dvec3 newPosition);

    glm::dvec3 GetPosition();

	int GetColliderID();

    void Translate(glm::dvec3 position);

    void Rotate(glm::dvec3 angVelocity, float deltaTime);

    void StaticSet();

private:
    ///Collider ID
    unsigned int m_colliderID;
    ///Extents of Bounding Box
    glm::dvec3 extents = {};
};

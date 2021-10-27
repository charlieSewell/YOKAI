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
     * @brief Set the Extents of the Bounding Box
     * @param extent 
     */
    void RenderGUI();
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

    void SetCentreOfMass(glm::vec3 com);
    glm::vec3 GetCentreOfMass();

    void SetInertiaTensor();
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

    glm::dvec3 GetExtents();

	/**
	* @brief Set the Positin of the Bounding Box
	* @param orientation
	*/
	void SetPosition(glm::vec3 newPosition);

    glm::vec3 GetPosition();

	int GetColliderID();

    void Translate(glm::vec3 velocity);

    void Rotate(glm::vec3 angVelocity, float deltaTime);

    void StaticSet();

    void SetCollisionCategory(unsigned short category);
    void SetCollisionMaskBits(unsigned short maskBits);

private:
    ///Collider ID
    unsigned int m_colliderID;
    ///Extents of Bounding Box
    glm::vec3 extents = {};

    glm::vec3 m_offset = {};
};

//PhysicsComponemt.hpp

#pragma once

#include "Controller/Physics/PhysicsSystem.hpp"
#include "Controller/EventManager.hpp"
#include "Model/Components/Transform.hpp"

/**
 * @class PhysicsComponent
 * @brief Physics component to be attatched to object
 */
class PhysicsComponent
{
public:
  /**
   * @brief Updates Physics
   * @param float - movementSpeed
   * @param float - jumpSpeed
   */
	void updatePhysics();

  /**
   * @brief Constructor For Physics Components
   */
	PhysicsComponent()=default;

	/**
	* @brief Constructor For Physics Components
	* @param Transfomr - transform
	*/
	PhysicsComponent(Transform &transform);

    /**
   * @brief Destructor For Physics Components
   */
	virtual ~PhysicsComponent() = default;

    /**
     * @brief Register ReactBoxShape
     * @param vec3* - position
     * @param float - width
     * @param float - length
     * @param float - height
     */
    void registerAABB(unsigned int ID, float width, float height, float length);
    /**
     * @brief Registers class in LUA
     */
    static void registerPhysicsComponent();
    /**
     * @brief Returns the rigid body of game object
     * @return
     */
    RigidBody * getCollider() const;
    /**
     * @brief Deletes the Collider
     */
    void deleteCollider();
    /**
     * @brief Registers Sphere
     * @param ID
     * @param radius
     */
    void registerSphere(unsigned int ID, float radius);
    /**
     * @brief Registers Physics Toggle
     */
	void registerPhysicsToggle();
    ///ReactBoxShape Collider
	//ReactBoxShape* m_collider;
    ///Objects Mass
	float m_mass;
    ///is on ground
	bool m_onGround = false;
    ///is collision detected
	bool m_collisionDetected;
    ///is collision resolved
	bool m_resolvingCollision;
    ///is physics active
	bool m_physicsActive = true;
	///Max Velocity
	float maxVelocity =0 ;
	/**
	 * @brief Sets the max Velocity
	 * @param vel
	 */
    void setmaxVelocity(float vel){maxVelocity = vel;}
    /**
     * @brief Gets the Max Velocity
     * @return
     */
    int getmaxVelocity() const{ return static_cast<int>(maxVelocity);}
    /**
     * @brief Gets the current velocity
     * @return
     */
	glm::vec3 getCurrentVelocity(){return getCollider()->GetLinearVelocity();}
private:

    ///is physics toggle pressed
	bool m_physicsTogglePressed = false;
	///colliderID
	int colliderID = -1;
	///transform Pointer
	Transform* m_transformPtr;
};

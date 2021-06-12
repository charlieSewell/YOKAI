#pragma once

#include "Model/Components/Transform.hpp"
#include "Model/Components/RayCaster.hpp"
//#include "Controller/GameObjectManager.hpp"
#include "Controller/EventManager.hpp"
#include "Controller/LuaManager.hpp"
#include <glm/gtc/random.hpp>
/**
 * @class AutomatedBehaviours
 * @brief Behaviours for AI
 */
class AutomatedBehaviours
{
public:
	
    /**
     * @brief Constructor for automated behaviours
     * @param transform
     */
	AutomatedBehaviours(Transform& transform);
    /**
     * @brief Accelerates the game object
     * @param topSpeed
     */
	void accelerate(float topSpeed);
    /**
     * @brief Decelerates the game object
     * @param topSpeed
     */
	void decelerate();
	/**
	 * @brief Seeks out a target position
	 * @param tartgetPosition
	 */
	void seek(glm::vec3 tartgetPosition);
	/**
	 * @brief Randomly wanders around
	 */
	void wander();
	
    /**
     * @brief Registers class in lua
     */
	static void registerClass();
    ///Heading of AI
	glm::vec3 heading;
	///angle
	float angle;
	///AI Top speed
	float topSpeed;
	///Ai current acceleration
	float acceleration;
	///AI rotation speed
	float rotationSpeed;
	///AI state
	int state;
    ///is AI active
	bool active;	// bad
    ///Raycaster for feelers
	RayCaster rayCaster;
	///Vector for right feeler
	glm::vec3 feelerRight;
    ///Vector for left feeler
	glm::vec3 feelerLeft;

	///has front feeler hit
	int frontFeelerHit = -1;
	///has right feeler hit
	int feelerRightHit = -1;
	///has left feeler hit
	int feelerLeftHit = -1;
    /**
     * @brief Updates the feelers
     */
	void updateFeelers();

private:
    ///Pointer to gameobjects transform
	Transform *m_transformPtr;
    ///AI wander angle
	float m_wanderAngle;
	/**
	 * @brief Updates AI Heading
	 */
	void updateHeading();
	/**
	 * @brief converts vector into an angle
	 * @param vector
	 * @return angle
	 */
	float angle_XZ(glm::vec3 vector);
};

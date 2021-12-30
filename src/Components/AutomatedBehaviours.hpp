#pragma once

#include "Transform.hpp"
#include "Components/RayCaster.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include <glm/gtc/random.hpp>

/**
 * @class AutomatedBehaviours
 * @brief Behaviours for AI
 */
class AutomatedBehaviours : public Component
{
public:
	
    /**
     * @brief Constructor for automated behaviours
     * @param transform
     */
	AutomatedBehaviours(GameObject* parent);
    /**
     * @brief Accelerates the game object
     * @param topSpeed
     */

	void accelerate();
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
	 * @brief Evades from target position
	 * @param tartgetPosition 
	 */
	void evade(glm::vec3 tartgetPosition);
	/**
	 * @brief Randomly wanders around
	 */
	void wander();
	
    ///Heading of AI
	glm::vec3 Heading = glm::vec3(0.5f, 0, 0.5f);
	///angle
	float Angle = 0;
	///AI Top speed
	float TopSpeed = 0;
	///Ai current acceleration
	float Acceleration = 0;
	///Ai Acceleration Rate
	float AccelerationRate = 0.0001;
	///AI rotation speed
	float RotationSpeed = 0;
	///AI state
	int State = 0;
    ///is AI active
	bool IsActive = false;	// bad
	///Vector for right feeler
	glm::vec3 feelerRight = glm::vec3(0);
    ///Vector for left feeler
	glm::vec3 feelerLeft = glm::vec3(0);

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

	void SetCastHeight(float castHeight);
	void SetCastDistance(float castDistance);

private:
    ///Pointer to gameobjects transform
	std::shared_ptr<Transform> m_transform = nullptr;
	///Raycaster for feelers
	std::shared_ptr <RayCaster> m_rayCaster = nullptr;
    ///AI wander angle
	float m_wanderAngle = 0;
	///Distance of raycaster hit
	float m_castHeight = 0;
	bool m_isCastHeightSet = false;
	float m_castDistance = 10;

	/**
	 * @brief Updates AI Heading
	 */
	void updateHeading();
	/**
	 * @brief Calculates rotation to a target position
	 * @param tartgetPosition 
	 */
	void calculateRotation(glm::vec3 tartgetPosition);
	/**
	 * @brief converts vector into an angle
	 * @param vector
	 * @return angle
	 */
	float angle_XZ(glm::vec3 vector);
};

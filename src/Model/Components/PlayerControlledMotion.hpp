//PlayerControlledMotion.hpp - Abstract class
#pragma once

#include "Model/Components/Transform.hpp"
#include "Controller/EventManager.hpp"
#include "Controller/Export.hpp"

/**
 * @class PlayerControlledMotion
 * @brief Player Control component that can be attatched to game object
 */
class YOKAI_API PlayerControlledMotion : public Component
{
public:
	
	PlayerControlledMotion(GameObject* parent);
  /**
   * @brief Setter for Player Movement speed
   * @param float - movementSpeed
   */
	void setMovementSpeed(float newMovementSpeed);
    /**
     * @brief Getter for Player Movement Speed
     * @return float
     */
	float getMovementSpeed() const;
    /**
     * @brief Setter for Jump Height
     * @param float - jumpHeight
     */
	void setJumpHeight(float jumpHeight);;

//protected:
  /**
   * @brief Constructor for Player Controlled Motion
   */
	//PlayerControlledMotion() {}

	/**
	* @brief Constructor for Player Controlled Motion
	* @param vec3* - positionPtr
	*/
	//PlayerControlledMotion(Transform &transform);
    /**
     * @brief Destructor for player controlled motion
     */
	virtual ~PlayerControlledMotion() {}
    /**
     * @brief Registers Movement with EMS
     * @param vec3& - position
     * @param vec3& - frontDirection
     * @param vec3& upDirection
     */
	void registerAllMovement(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position);
    /**
     * @brief Registers Forwared movement with EMS
     * @param vec3& - position
     * @param vec3& - frontDirection
     */
	void registerMoveForward(glm::vec3& frontDirection, glm::vec3& position);
    /**
     * @brief Registers Backwards movement with EMS
     * @param vec3& - position
     * @param vec3& - frontDirection
     */
	void registerMoveBackward(glm::vec3& frontDirection, glm::vec3& position);
    /**
     * @brief Registers Left movement with EMS
     * @param vec3& - position
     * @param vec3& - frontDirection
     * @param vec3& - upDirection
     */
	void registerMoveLeft(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position);
    /**
     * @brief Registers Right movement with EMS
     * @param vec3& - position
     * @param vec3& - frontDirection
     * @param vec3& - upDirection
     */
	void registerMoveRight(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position);
	/**
	 * @brief Registers jump with EMS
	 * @param vec3& - position
	 * @param vec3& - upDirection
	 */
    void registerJump(glm::vec3& upDirection, glm::vec3& position);
	/**
	* @brief Registers sprint with EMS
	*/
	void registerSprint();
    /**
     * @brief Registers downward movement with EMS
     * @param vec3& - position
     * @param vec3& - upDirection
     */
	void registerMoveDown(glm::vec3& upDirection, glm::vec3& position);
    /**
     * Registers Mouse Movement with EMS
     * @param vec3& - frontDirection
     */
	void registerXYLook(glm::vec3& frontDirection);

	///actual sprint multiplier - equals 1 when inactive
	float sprint;
	// sprint multiplier assigned when active
	float sprintMultiplier = 0.05;
    ///Movement speed
	float movementSpeed = 0.01f;
    ///Mouse sensitivity
	double lookSensitivity = 0.05f;
	///Mouse sensitivity Multiplier
	double lookSensitivityMultiplier = 1.0f;
    ///bool to check if player can jump
	bool canJump;
    ///bool to say whether player is in jump
	bool jumping = false;
    ///player jump speed
	float jumpSpeed;
    glm::vec3 updateVector = glm::vec3(1.0);
private:
    ///Jump height target
	float m_jumpTarget;
    ///Current jump decay
	float m_jumpDecay;
    ///Pointer to current transform
	Transform* m_transformPtr;
};

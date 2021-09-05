//PlayerControlledMotion.cpp

#include "PlayerControlledMotion.hpp"

PlayerControlledMotion::PlayerControlledMotion(GameObject* parent)
	: Component(parent)
{

}


void PlayerControlledMotion::setMovementSpeed(float newMovementSpeed)
{
	movementSpeed = newMovementSpeed;
}

float PlayerControlledMotion::getMovementSpeed() const
{
	return movementSpeed;
}


void PlayerControlledMotion::registerAllMovement(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position)
{
	registerMoveForward(frontDirection, position);
	registerMoveBackward(frontDirection, position);
	registerMoveLeft(frontDirection, upDirection, position);
	registerMoveRight(frontDirection, upDirection, position);
	registerJump(upDirection, position);
	registerSprint();
	registerMoveDown(upDirection, position);
	registerXYLook(frontDirection);
}

void PlayerControlledMotion::registerMoveForward(glm::vec3& frontDirection, glm::vec3& position)
{
	auto moveForward = [&]()
	{
		position += glm::vec3(frontDirection.x, 0, frontDirection.z) * movementSpeed;
	};
	EMS::getInstance().add(NoReturnEvent::moveForward, moveForward);
}

void PlayerControlledMotion::registerMoveBackward(glm::vec3& frontDirection, glm::vec3& position)
{
	auto moveBackward = [&]()
	{
		position -= glm::vec3(frontDirection.x, 0, frontDirection.z) * movementSpeed;
	};
	EMS::getInstance().add(NoReturnEvent::moveBackward, moveBackward);
}

void PlayerControlledMotion::registerMoveLeft(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position)
{
	auto moveLeft = [&]()
	{
		position -= glm::normalize(glm::cross(frontDirection, upDirection)) * movementSpeed;
	};
	EMS::getInstance().add(NoReturnEvent::moveLeft, moveLeft);
}

void PlayerControlledMotion::registerMoveRight(glm::vec3& frontDirection, glm::vec3& upDirection, glm::vec3& position)
{
	auto moveRight = [&]()
	{
		position += glm::normalize(glm::cross(frontDirection, upDirection)) * movementSpeed;
	};
	EMS::getInstance().add(NoReturnEvent::moveRight, moveRight);
}

void PlayerControlledMotion::registerMoveDown(glm::vec3& upDirection, glm::vec3& position)
{
	auto moveDown = [&]()
	{
        position -= upDirection * movementSpeed;
	};
	EMS::getInstance().add(NoReturnEvent::moveDown, moveDown);
}


void PlayerControlledMotion::registerJump(glm::vec3& upDirection, glm::vec3& position)
{
	auto jump = [&]()
	{
        if (true)
		{
               position += upDirection * movementSpeed;
		}
    };  
	EMS::getInstance().add(NoReturnEvent::jump, jump);
}

void PlayerControlledMotion::registerSprint()
{
	auto sprintOn = [&]()
	{
		sprint = sprintMultiplier;
	};

	EMS::getInstance().add(NoReturnEvent::sprintPressed, sprintOn);

	auto sprintOff = [&]()
	{
		sprint = 1.0;
	};

	EMS::getInstance().add(NoReturnEvent::sprintReleased, sprintOff);
}

void PlayerControlledMotion::registerXYLook(glm::vec3& frontDirection)
{
	static double yaw = -90.0f;
	static double pitch = 0.0f;

	auto xyLook = [&](double xoffset, double yoffset) 
	{
		xoffset *= lookSensitivity * lookSensitivityMultiplier;
		yoffset *= lookSensitivity * lookSensitivityMultiplier;

		yaw += xoffset;
		pitch -= yoffset;

		// stops bad weird camera movement
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f) 
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		frontDirection = glm::normalize(direction);
	};

	EMS::getInstance().add(NoReturnEvent::xyLook, xyLook);
}
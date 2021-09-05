//InputManagerGLFW.cpp

#include "InputManagerGLFW.hpp"

InputManagerGLFW& InputManagerGLFW::getInstance()
{
	static InputManagerGLFW instance;
	return instance;
}

void InputManagerGLFW::processKeyboard(GLFWwindow* window)
{

	if(!glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		m_keys['w'] = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
		m_keys['s'] = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
		m_keys['a'] = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
		m_keys['d'] = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
		m_keys[' '] = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
		m_keys['c'] = (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS);

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			EMS::getInstance().fire(NoReturnEvent::closePressed);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
			EMS::getInstance().fire(NoReturnEvent::closeReleased);
	}
}

void InputManagerGLFW::processMouse(GLFWwindow* window)
{
	if (!glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			EMS::getInstance().fire(NoReturnEvent::mouseClicked);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
			EMS::getInstance().fire(NoReturnEvent::mouseReleased);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			EMS::getInstance().fire(NoReturnEvent::mouse2Clicked);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
			EMS::getInstance().fire(NoReturnEvent::mouse2Released);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (!mouseInit)
		{
			lastX = xpos;
			lastY = ypos;
			mouseInit = true;
		}

		double xoffset = xpos - lastX;
		double yoffset = ypos - lastY;

		m_mouseOffset.x = xoffset;
		m_mouseOffset.y = yoffset;

		//EMS::getInstance().fire(NoReturnEvent::xyLook, xoffset, yoffset);

		lastX = xpos;
		lastY = ypos;
	}
}

void InputManagerGLFW::processGamepadButtons()
{
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		GLFWgamepadstate state;

		if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
		{
			if (state.buttons[GLFW_GAMEPAD_BUTTON_A])
				EMS::getInstance().fire(NoReturnEvent::jump);		
	
			if(state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB])
				EMS::getInstance().fire(NoReturnEvent::moveDown);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::togglePhysicsPressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::togglePhysicsReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::toggleWireFramePressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::toggleWireFrameReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::toggleMenuPressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::toggleMenuReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::pausePressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::pauseReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::reloadPressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::reloadReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::meleePressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::meleeReleased);

			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB] == GLFW_PRESS)
				EMS::getInstance().fire(NoReturnEvent::sprintPressed);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB] == GLFW_RELEASE)
				EMS::getInstance().fire(NoReturnEvent::sprintReleased);
		}
	}
}

void InputManagerGLFW::processGamepadAxis()
{
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		GLFWgamepadstate state;

		if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
		{
			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.25)
				EMS::getInstance().fire(NoReturnEvent::moveForward);

			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.25)
				EMS::getInstance().fire(NoReturnEvent::moveBackward);

			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.25)
				EMS::getInstance().fire(NoReturnEvent::moveLeft);

			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.25)
				EMS::getInstance().fire(NoReturnEvent::moveRight);

			if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > 0.25)
				EMS::getInstance().fire(NoReturnEvent::mouseClicked);
			if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] < -0.25)
				EMS::getInstance().fire(NoReturnEvent::mouseReleased);

			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > 0.25)
				EMS::getInstance().fire(NoReturnEvent::mouse2Clicked);
			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] < -0.25)
				EMS::getInstance().fire(NoReturnEvent::mouse2Released);

			double lookx(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
			double looky(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);

			EMS::getInstance().fire(NoReturnEvent::xyLook, lookx * 20, looky * 20);
		}
	}
}
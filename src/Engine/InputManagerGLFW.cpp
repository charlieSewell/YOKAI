#include "InputManagerGLFW.hpp"

//TODO CONNOR: CLEAN

InputManagerGLFW::InputManagerGLFW()
{
	createMap();
}

InputManagerGLFW& InputManagerGLFW::getInstance()
{
	static InputManagerGLFW instance;
	return instance;
}

void InputManagerGLFW::processKeyboard(GLFWwindow* window)
{

	if(!glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		for(int i=0; i < m_activeKeys.size(); ++i)
		{
			m_keyStates[m_activeKeys[i]] = (glfwGetKey(window, m_keyMap[m_activeKeys[i]]) == GLFW_PRESS);
		}
	}

		//TODO CONNOR: This needs to get moved out
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			EMS::getInstance().fire(NoReturnEvent::pausePressed);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
			EMS::getInstance().fire(NoReturnEvent::pauseReleased);
}

void InputManagerGLFW::processMouse(GLFWwindow* window)
{
	if (!glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		glfwGetCursorPos(window, &m_mouse.position.x, &m_mouse.position.y);

		if (!mouseInit)
		{
			lastX = m_mouse.position.x;
			lastY = m_mouse.position.y;
			mouseInit = true;
		}

		m_mouse.offset.x = m_mouse.position.x - lastX;
		m_mouse.offset.y = m_mouse.position.y - lastY;

		lastX = m_mouse.position.x;
		lastY = m_mouse.position.y;
	}
}

//TODO CONNOR: UPDATE GAMEPAD INPUT
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

			//EMS::getInstance().fire(NoReturnEvent::xyLook, lookx * 20, looky * 20);
		}
	}
}

void InputManagerGLFW::createMap()
{
	// Special keys can take indexes 0-32 (excluding 27=ESC) as the ASCII defintions are not on the keyboard
	m_keyMap[(unsigned int)YOKAI_INPUT::LEFT_CONTROL] = GLFW_KEY_LEFT_CONTROL;
	m_keyMap[(unsigned int)YOKAI_INPUT::LEFT_SHIFT] = GLFW_KEY_LEFT_SHIFT;
	m_keyMap[(unsigned int)YOKAI_INPUT::LEFT_ALT] = GLFW_KEY_LEFT_SHIFT;
	m_keyMap[(unsigned int)YOKAI_INPUT::RIGHT_SHIFT] = GLFW_KEY_RIGHT_CONTROL;
	m_keyMap[(unsigned int)YOKAI_INPUT::RIGHT_CONTROL] = GLFW_KEY_RIGHT_SHIFT;
	m_keyMap[(unsigned int)YOKAI_INPUT::RIGHT_ALT] = GLFW_KEY_RIGHT_SHIFT;
	m_keyMap[(unsigned int)YOKAI_INPUT::ENTER] = GLFW_KEY_ENTER;
	m_keyMap[(unsigned int)YOKAI_INPUT::TAB] = GLFW_KEY_TAB;
	m_keyMap[(unsigned int)YOKAI_INPUT::BACKSPACE] = GLFW_KEY_BACKSPACE;
	m_keyMap[(unsigned int)YOKAI_INPUT::LEFT_MOUSE_BUTTON] = GLFW_MOUSE_BUTTON_1;
	m_keyMap[(unsigned int)YOKAI_INPUT::RIGHT_MOUSE_BUTTON] = GLFW_MOUSE_BUTTON_2;

	// These keys corrospond and resolve to their ASCII Value
	m_keyMap[(unsigned int)YOKAI_INPUT::ESCAPE] = GLFW_KEY_ESCAPE;
	m_keyMap[(unsigned int)YOKAI_INPUT::DELETE] = GLFW_KEY_DELETE;
	m_keyMap[(unsigned int)YOKAI_INPUT::SPACE] = GLFW_KEY_SPACE;
	m_keyMap[(unsigned int)YOKAI_INPUT::COMMA] = GLFW_KEY_COMMA;
	m_keyMap[(unsigned int)YOKAI_INPUT::MINUS] = GLFW_KEY_MINUS;
	m_keyMap[(unsigned int)YOKAI_INPUT::PERIOD] = GLFW_KEY_PERIOD;
	m_keyMap[(unsigned int)YOKAI_INPUT::SLASH] = GLFW_KEY_SLASH;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_0] = GLFW_KEY_0;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_1] = GLFW_KEY_1;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_2] = GLFW_KEY_2;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_3] = GLFW_KEY_3;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_4] = GLFW_KEY_4;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_5] = GLFW_KEY_5;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_6] = GLFW_KEY_6;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_7] = GLFW_KEY_7;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_8] = GLFW_KEY_8;
	m_keyMap[(unsigned int)YOKAI_INPUT::NUM_9] = GLFW_KEY_9;
	m_keyMap[(unsigned int)YOKAI_INPUT::SEMICOLON] = GLFW_KEY_SEMICOLON;;
	m_keyMap[(unsigned int)YOKAI_INPUT::EQUAL] = GLFW_KEY_EQUAL;
	m_keyMap[(unsigned int)YOKAI_INPUT::A] = GLFW_KEY_A;
	m_keyMap[(unsigned int)YOKAI_INPUT::B] = GLFW_KEY_B;
	m_keyMap[(unsigned int)YOKAI_INPUT::C] = GLFW_KEY_C;
	m_keyMap[(unsigned int)YOKAI_INPUT::D] = GLFW_KEY_D;
	m_keyMap[(unsigned int)YOKAI_INPUT::E] = GLFW_KEY_E;
	m_keyMap[(unsigned int)YOKAI_INPUT::F] = GLFW_KEY_F;
	m_keyMap[(unsigned int)YOKAI_INPUT::G] = GLFW_KEY_G;
	m_keyMap[(unsigned int)YOKAI_INPUT::H] = GLFW_KEY_H;
	m_keyMap[(unsigned int)YOKAI_INPUT::I] = GLFW_KEY_I;
	m_keyMap[(unsigned int)YOKAI_INPUT::J] = GLFW_KEY_J;
	m_keyMap[(unsigned int)YOKAI_INPUT::K] = GLFW_KEY_K;
	m_keyMap[(unsigned int)YOKAI_INPUT::L] = GLFW_KEY_L;
	m_keyMap[(unsigned int)YOKAI_INPUT::M] = GLFW_KEY_M;
	m_keyMap[(unsigned int)YOKAI_INPUT::N] = GLFW_KEY_N;
	m_keyMap[(unsigned int)YOKAI_INPUT::O] = GLFW_KEY_O;
	m_keyMap[(unsigned int)YOKAI_INPUT::P] = GLFW_KEY_P;
	m_keyMap[(unsigned int)YOKAI_INPUT::Q] = GLFW_KEY_Q;
	m_keyMap[(unsigned int)YOKAI_INPUT::R] = GLFW_KEY_R;
	m_keyMap[(unsigned int)YOKAI_INPUT::S] = GLFW_KEY_S;
	m_keyMap[(unsigned int)YOKAI_INPUT::T] = GLFW_KEY_T;
	m_keyMap[(unsigned int)YOKAI_INPUT::U] = GLFW_KEY_U;
	m_keyMap[(unsigned int)YOKAI_INPUT::V] = GLFW_KEY_V;
	m_keyMap[(unsigned int)YOKAI_INPUT::W] = GLFW_KEY_W;
	m_keyMap[(unsigned int)YOKAI_INPUT::X] = GLFW_KEY_X;
	m_keyMap[(unsigned int)YOKAI_INPUT::Y] = GLFW_KEY_Y;
	m_keyMap[(unsigned int)YOKAI_INPUT::Z] = GLFW_KEY_Z;
	m_keyMap[(unsigned int)YOKAI_INPUT::LEFT_BRACKET] = GLFW_KEY_LEFT_BRACKET;
	m_keyMap[(unsigned int)YOKAI_INPUT::BACKSLASH]= GLFW_KEY_BACKSLASH;
	m_keyMap[(unsigned int)YOKAI_INPUT::RIGHT_BRACKET] = GLFW_KEY_RIGHT_BRACKET;
	m_keyMap[(unsigned int)YOKAI_INPUT::GRAVE_ACCENT] = GLFW_KEY_GRAVE_ACCENT;
}

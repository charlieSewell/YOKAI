//InputManagerGLFW.cpp

#include "InputComponent.hpp"

Input::Input(GameObject* parent)
	: Component(parent)
{

}

bool Input::GetKeyState(unsigned int key)
{
	key = towupper(key);

	if(!InputManagerGLFW::getInstance().m_keyActive[key])
	{
		InputManagerGLFW::getInstance().m_keyActive[key] = true;
		InputManagerGLFW::getInstance().m_activeKeys.push_back(key);
	}

	return(InputManagerGLFW::getInstance().m_keyStates[key]);
}

bool Input::GetKeyState(YOKAI_INPUT key)
{
	return(GetKeyState((unsigned int)key));
}

bool Input::GetKeyToggle(YOKAI_INPUT key)
{
	if (!InputManagerGLFW::getInstance().m_keyActive[(unsigned int)key])
	{
		m_toggleStates[key] = GetKeyState((unsigned int)key);
		return m_toggleStates[key];
	}
	else
	{
		bool keyState = GetKeyState((unsigned int)key);
		if(!m_toggleStates[key] && keyState)
		{
			m_toggleStates[key] = true;
			return m_toggleStates[key];
		}
		else
		{
			m_toggleStates[key] = keyState;
			return false;
		}
	}
}

Mouse Input::GetMouseState()
{
	return(InputManagerGLFW::getInstance().m_mouse);
}


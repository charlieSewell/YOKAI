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

Mouse Input::GetMouseState()
{
	return(InputManagerGLFW::getInstance().m_mouse);
}


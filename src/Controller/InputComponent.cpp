//InputManagerGLFW.cpp

#include "InputComponent.hpp"

Input::Input(GameObject* parent)
	: Component(parent)
{

}

bool Input::GetKeyState(unsigned int key)
{
	return(InputManagerGLFW::getInstance().m_keys[key]);
}

MouseOffset Input::GetMouseOffset()
{
	return(InputManagerGLFW::getInstance().m_mouseOffset);
}


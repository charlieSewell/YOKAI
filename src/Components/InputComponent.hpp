#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <wctype.h>
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Engine/InputManagerGLFW.hpp"
#include <map>

/**
 * @class InputManagerGLFW
 * @brief Manages the GLFW input
 */
class YOKAI_API Input : public Component
{
  public:
  	Input();
	/**
	 * @brief Construct a new Input object
	 * @param parent 
	 */
	Input(GameObject* parent);
	/**
	* @brief Get the Key State
	* @param key 
	* @return bool
	*/
	bool GetKeyState(unsigned int key);
	/**
	* @brief Get the Key State
	* @param key 
	* @return bool
	*/
	bool GetKeyState(YOKAI_INPUT key);
	/**
	* @brief Get the Key toggle State
	* @param key
	* @return bool
	*/
	bool GetKeyToggle(YOKAI_INPUT key);
	/**
	* @brief Get the Mouse State
	* @return Mouse
	*/
	Mouse GetMouseState();
	/**
	 * @brief Shows Mouse
	 */
	void ShowMouse();
	/**
	 * @brief Hides Mouse
	 */
	void HideMouse();
  private:
	///Map of whether keys have been toggled
	std::map<YOKAI_INPUT, bool> m_toggleStates;
};
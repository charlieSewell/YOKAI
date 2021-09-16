#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "EventManager.hpp"
#include "Components/Camera.hpp"
#include <map>
#include <vector>

/**
 * @class InputManagerGLFW
 * @brief Manages the GLFW input
 */

enum class SPECIAL
{
	LEFT_SHIFT			= 0,
	LEFT_CONTROL		= 1,
	LEFT_ALT			= 3,	
	RIGHT_SHIFT			= 4,
	RIGHT_CONTROL		= 5,
	RIGHT_ALT			= 6,
	ENTER				= 7,
	TAB					= 8,
	BACKSPACE			= 9,
	LEFT_MOUSE_BUTTON	= 10,
	RIGHT_MOUSE_BUTTON	= 11
};

struct Mouse
{
	struct
	{
		double x;
		double y;
	} position;

	struct
	{
		double x;
		double y;
	} offset;
};

class InputManagerGLFW
{
  public:
    /**
     * Returns this instance of InputManagerGLFW
     * @return InputManagerGLFW&
     */
	  static InputManagerGLFW& getInstance();
      ///Deleted copy constructor
	  InputManagerGLFW(InputManagerGLFW const&) = delete;
      ///Deleted = operator
	  void operator=(InputManagerGLFW const&) = delete;
      /**
       * @brief Processes Keyboard Input
       * @param GLFWwindow* - window
       */
	  void processKeyboard(GLFWwindow * window);
      /**
       * @brief Processes Mouse Input
       * @param GLFWwindow* - window
       */
	  void processMouse(GLFWwindow* window);

		/**
		* @brief Processes gamepad button Input	
		*/
	  void processGamepadButtons();

		/**
		* @brief Processes gamepad axis Input
		*/
	  void processGamepadAxis();

	  //TODO CONNOR: These will be private with Getter/Setter
	  bool m_keyStates[128];
	  bool m_keyActive[128];
	  std::vector<unsigned int> m_activeKeys;

	  Mouse m_mouse;

  private:
      /**
       * @brief Privatised constructor for Singleton Pattern
       */
	  InputManagerGLFW();
      ///Mouse Init
	  bool mouseInit = false;
      ///Last Mouse X and Y
	  double lastX, lastY;

	  std::map<unsigned int, unsigned int> m_keyMap;
	  void createMap();
};
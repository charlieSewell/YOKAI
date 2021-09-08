#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
#include "Controller/InputManagerGLFW.hpp"

/**
 * @class InputManagerGLFW
 * @brief Manages the GLFW input
 */
class YOKAI_API Input : public Component
{
  public:
	  Input(GameObject* parent);
	  bool GetKeyState(unsigned int key);
	  bool GetKeyState(SPECIAL key);
	  Mouse GetMouseState();
  private:
};
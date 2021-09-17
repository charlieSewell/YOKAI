#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <wctype.h>
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Engine/InputManagerGLFW.hpp"
/**
 * @class InputManagerGLFW
 * @brief Manages the GLFW input
 */
class YOKAI_API Input : public Component
{
  public:
	  Input(GameObject* parent);
	  bool GetKeyState(unsigned int key);
	  bool GetKeyState(YOKAI_INPUT key);
	  Mouse GetMouseState();
  private:
};
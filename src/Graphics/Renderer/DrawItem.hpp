#pragma once
#include "Mesh.hpp"
#include<glm/glm.hpp>

class Mesh;
namespace RENDER 
{
  struct DrawItem 
  {
    glm::mat4 transform = {};
    std::vector<glm::mat4> finalTransforms;
    bool isAnimated = false;
    Mesh* mesh = nullptr;
  };
}

#pragma once
#include "Model/Mesh.hpp"
#include<glm/glm.hpp>

class Mesh;
class bgfxShader;
namespace RENDER 
{
  struct DrawItem 
  {
    glm::mat4 transform = {};
    std::vector<glm::mat4> finalTransforms;
    //TODO: camera pos needs to be propegated from player at some point
    glm::vec3 camPos = glm::vec3(10000.0f,10000.0f,10000.0f);
    uint16_t viewID = 0;
    uint64_t state = 0;
    bool isAnimated = false;
    std::shared_ptr<bgfxShader> shader = nullptr;
    Mesh* mesh = nullptr;
  };
}

#pragma once
#include "Model/Mesh.hpp"
#include<glm/glm.hpp>

class Mesh;
struct DrawItem {
  glm::mat4 transform = {};
  Mesh* mesh = nullptr;
};
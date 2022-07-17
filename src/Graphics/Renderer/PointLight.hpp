#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

/**
 * @struct PointLight
 * @brief Stores point light info for GPU
 */
struct PointLight
{
  // position of the Light
  glm::vec3 position;
  // radiant flux in W
  glm::vec3 flux;
  
  float radius;
};
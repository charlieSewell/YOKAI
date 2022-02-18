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
  // calculate an appropriate radius for light culling
  // a windowing function in the shader will perform a smooth transition to zero
  // this is not physically based and usually artist controlled
  float CalculateRadius() const;
};
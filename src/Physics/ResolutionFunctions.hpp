#pragma once
#include <glm/glm.hpp>

#define PI 3.14159265358979323846

namespace YokaiPhysics 
{
    /**
     * @brief Calculates Rectangular Inertia Tensor
     * @param ext 
     * @param mass 
     * @return glm::mat3x3 
     */
    glm::mat3x3 RectangleInertiaTensor(glm::vec3 ext, float mass);
    /**
     * @brief Calculates Spherical Inertia Tensor
     * @param radius 
     * @param mass 
     * @return glm::mat3x3 
     */
    glm::mat3x3 SphereInertiaTensor(float radius, float mass);
    /**
     * @brief Degrees To radians
     * @param degrees 
     * @return float 
     */
    float DegreesToRadians(float degrees);
    /**
     * @brief Radians to Degrees
     * @param radians 
     * @return float 
     */
    float RadiansToDegrees(float radians);
}
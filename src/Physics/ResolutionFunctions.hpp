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
    glm::mat3x3 RectangleInertiaTensor(glm::dvec3 ext, double mass);
    /**
     * @brief Calculates Spherical Inertia Tensor
     * @param radius 
     * @param mass 
     * @return glm::mat3x3 
     */
    glm::mat3x3 SphereInertiaTensor(double radius, double mass);
    /**
     * @brief Degrees To radians
     * @param degrees 
     * @return double 
     */
    double DegreesToRadians(double degrees);
    /**
     * @brief Radians to Degrees
     * @param radians 
     * @return double 
     */
    double RadiansToDegrees(double radians);
}
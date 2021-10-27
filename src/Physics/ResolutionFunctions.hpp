#pragma once
#include <glm/glm.hpp>

#define PI 3.14159265358979323846

namespace YokaiPhysics {

    double AverageAngularVelocity(double arcStart, double arcEnd, double time, double radius);

    double AngularDisplacement(double arc, double radius);

    double AverageAngularAcceleration(double angularVelocityStart, double angularVelocityEnd, double time);

    double TangentialVelocity(double omega, double radius);

    double TangentialAcceleration(double angularAcceleration, double radius);

    glm::mat3x3 RectangleInertiaTensor(glm::dvec3 ext, double mass);

    glm::mat3x3 SphereInertiaTensor(double radius, double mass);

    double DegreesToRadians(double degrees);

    double RadiansToDegrees(double radians);
}
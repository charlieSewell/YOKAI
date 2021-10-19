#pragma once
#include <glm/glm.hpp>

namespace YokaiPhysics {

    double AverageAngularVelocity(double arcStart, double arcEnd, double time, double radius);

    double AngularDisplacement(double arc, double radius);

    double AverageAngularAcceleration(double angularVelocityStart, double angularVelocityEnd, double time);

    double TangentialVelocity(double omega, double radius);

    double TangentialAcceleration(double angularAcceleration, double radius);

    glm::dmat3x3 RectangleInertiaTensor(double mass);

    glm::dmat3x3 SphereInertiaTensor(double mass);
}
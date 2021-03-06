#include "ResolutionFunctions.hpp"


glm::mat3x3 YokaiPhysics::RectangleInertiaTensor(glm::vec3 ext, float mass) 
{
    //Rectangular cylinder: Ixx = (1/12) m(a2 + l2); Iyy = (1/12) m(b2 + l2); Izz = (1/12) m(a2 + b2)
    glm::mat3x3 inertia(0.0);
    ext.x *= 2;
    ext.y *= 2;
    ext.z *= 2;
    // length / Ixx = (1/12) m(a2 + l2)
    inertia[0][0] = (1.0f / 12.0f) * mass * (ext.y * ext.y + ext.x * ext.x);

    // height / Iyy = (1/12) m(b2 + l2)
    inertia[1][1] = (1.0f / 12.0f) * mass * (ext.z * ext.z + ext.x * ext.x);

    // width / Izz = (1/12) m(a2 + b2)
    inertia[2][2] = (1.0f / 12.0f) * mass * (ext.z * ext.z + ext.y * ext.y);
    

    return inertia;
}

glm::mat3x3 YokaiPhysics::SphereInertiaTensor(float radius, float mass) 
{
    // Sphere: Ixx = Iyy = Izz = (2/5) mr2
    glm::dmat3x3 inertia{};

    inertia[0][0] = (2.0 / 5.0) * mass * (radius * radius);
    inertia[1][1] = (2.0 / 5.0) * mass * (radius * radius);
    inertia[2][2] = (2.0 / 5.0) * mass * (radius * radius);

    return inertia;
}

float YokaiPhysics::DegreesToRadians(float degrees) 
{
    return (degrees * (float(PI) / 180.0f));
}

float YokaiPhysics::RadiansToDegrees(float radians) 
{
    return (radians * (180.0f / float(PI)));
}
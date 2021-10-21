#include "ResolutionFunctions.hpp"

double YokaiPhysics::AverageAngularVelocity(double arcStart, double arcEnd, double time, double radius) 
{
    double initialDisplacement;
    double endDisplacement;
    double omega;

    initialDisplacement = arcStart / radius;
    endDisplacement     = arcEnd / radius;

    omega = (endDisplacement - initialDisplacement) / time;
    return omega;
}

double YokaiPhysics::AngularDisplacement(double arc, double radius) 
{
    double theta;
    theta = arc / radius;
    return theta;
}

double YokaiPhysics::AverageAngularAcceleration(double angularVelocityStart, double angularVelocityEnd, double time) 
{
    double alpha;
    alpha = (angularVelocityEnd - angularVelocityStart) / time;
    return alpha;
}

double YokaiPhysics::TangentialVelocity(double omega, double radius) 
{
    double tangential;
    tangential = omega * radius;
    return tangential;
}

double YokaiPhysics::TangentialAcceleration(double angularAcceleration, double radius) 
{
    double acceleration;
    acceleration = angularAcceleration * radius;
    return acceleration;
}

glm::mat3x3 YokaiPhysics::RectangleInertiaTensor(glm::vec3 ext, float mass) 
{
    //Rectangular cylinder: Ixx = (1/12) m(a2 + l2); Iyy = (1/12) m(b2 + l2); Izz = (1/12) m(a2 + b2)
    glm::mat3x3 inertia{};

    // length / Ixx = (1/12) m(a2 + l2)
    inertia[0][0] = (1.0 / 12.0) * mass * (ext.y * ext.y + ext.x * ext.x);

    // height / Iyy = (1/12) m(b2 + l2)
    inertia[1][1] = (1.0 / 12.0) * mass * (ext.z * ext.z + ext.x * ext.x);

    // width / Izz = (1/12) m(a2 + b2)
    inertia[2][2] = (1.0 / 12.0) * mass * (ext.z * ext.z + ext.y * ext.y);

    return inertia;
}

glm::mat3x3 SphereInertiaTensor(float radius, float mass) 
{
    // Sphere: Ixx = Iyy = Izz = (2/5) mr2
    glm::mat3x3 inertia{};

    inertia[0][0] = (2.0 / 5.0) * mass * (radius * radius);
    inertia[1][1] = (2.0 / 5.0) * mass * (radius * radius);
    inertia[2][2] = (2.0 / 5.0) * mass * (radius * radius);

    return inertia;
}
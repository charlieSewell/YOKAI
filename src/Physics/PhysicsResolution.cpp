#include "PhysicsResolution.hpp"

void PhysicsResolution::onContact(const rp3d::CollisionCallback::CallbackData &callbackData) 
{
    //std::cout << "Objects hit" << std::endl;

    /*
    double coefficientOfRestitution = 0.6;
    auto &transform1 = first_object->GetComponent<Transform>();
    auto &transform2 = second_object->GetComponent<Transform>();
    auto &collisionBody1 = first_object->GetComponent<CollisionBody>();
    auto &collisionBody2 = second_object->GetComponent<CollisionBody>();

    glm::dvec3 linearVelocity1 = collisionBody1.linearVelocity;
    glm::dvec3 angularVelocity1 = collisionBody1.angularVelocity;
    glm::dvec3 linearVelocity2 = collisionBody2.linearVelocity;
    glm::dvec3 angularVelocity2 = collisionBody2.angularVelocity;

    for (auto &n : collision.contact_points) {
        if ((collisionBody1.is_sleeping || collisionBody1.static_object) && (collisionBody2.is_sleeping || collisionBody2.static_object)) {
            continue;
        }

    glm::dvec3 r1 = n.first_body_contact_point - (transform1.pos + collisionBody1.centre_mass);
    glm::dvec3 r2 = n.second_body_contact_point - (transform2.pos + collisionBody2.centre_mass);

    if (!collisionBody1.is_sleeping && !collisionBody1.static_object) {
        transform1.pos += n.contact_normal * ((n.penetration / 2) * -1);
    }
    if (!collisionBody2.is_sleeping && !collisionBody2.static_object) {
        transform2.pos -= n.contact_normal * ((n.penetration / 2) * -1);
    }

    // Transfer of momentum

    //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
    // __________________________________________________________________________ * n̂
    // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

    //  -(1 + ε)
    double restitution = -(1.0 + coefficientOfRestitution);

    // (v⁻₁ - v⁻₂)
    glm::dvec3 relativeVelocity = linearVelocity1 - linearVelocity2;

    //(r₁ x n̂)
    auto r1xn = glm::cross(r1, n.contact_normal);

    //(r₂ x n̂)
    auto r2xn = glm::cross(r2, n.contact_normal);

    // (m₁⁻¹ + m₂⁻¹)
    double combinedInverseMass = collisionBody1.inverse_mass + collisionBody2.inverse_mass;

    //-(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
    auto numerator = restitution * (glm::dot(n.contact_normal, relativeVelocity) + glm::dot(angularVelocity1, r1xn) - glm::dot(angularVelocity2, r2xn));

    // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)
    float denominator = combinedInverseMass + (glm::dot(r1xn, collisionBody1.inverse_inertia_tensor * r1xn) + glm::dot(r2xn, collisionBody2.inverse_inertia_tensor * r2xn));

    //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
    // __________________________________________________________________________ * n̂
    // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

    // Transfer of momentum
    auto lambda = (numerator / denominator);

    // linear impulse
    auto linearImpulse = lambda * n.contact_normal;

    if (lambda < 0) 
    {
        // v⁺₁ = v⁻₁
        linearVelocity1 += linearImpulse * collisionBody1.inverseMass;
        // v⁺₂ = v⁻₂
        linearVelocity2 -= linearImpulse * collisionBody2.inverseMass;

        angularVelocity1 = angularVelocity1 + (lambda * collisionBody1.inverseInertiaTensor) * r1xn;
        angularVelocity2 = angularVelocity2 - (lambda * collisionBody2.inverseInertiaTensor) * r2xn;
    }
    */
}
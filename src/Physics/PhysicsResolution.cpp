#include "PhysicsResolution.hpp"

/*
void PhysicsResolution::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) {
    
    for (int p = 0; p < callbackData.getNbOverlappingPairs(); p++) {
        // Get the contact pair
        rp3d::OverlapCallback::OverlapPair overlapPair = callbackData.getOverlappingPair(p);

        int test1 = overlapPair.getCollider1()->getEntity().id;
        int test2 = overlapPair.getCollider2()->getEntity().id;

        if (!PhysicsSystem::getInstance().getPhysicsBody(test1)->getIsStaticObject()) {
            glm::dvec3 lv1 = PhysicsSystem::getInstance().getPhysicsBody(test1)->getLinearVelocity();
            PhysicsSystem::getInstance().getPhysicsBody(test1)->setLinearVelocity(-lv1);
        }
    }
}
*/

void PhysicsResolution::onContact(const rp3d::CollisionCallback::CallbackData &callbackData) 
{ 

    for (int p = 0; p < callbackData.getNbContactPairs(); p++) 
    {
        // Get the contact pair
        CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
        int test1                                  = contactPair.getCollider1()->getEntity().id;
        int test2                                  = contactPair.getCollider2()->getEntity().id;

        if (contactPair.getEventType() == CollisionCallback::ContactPair::EventType::ContactStart) {

            if (!PhysicsSystem::getInstance().getPhysicsBody(test1)->getIsStaticObject() &&
                !PhysicsSystem::getInstance().getPhysicsBody(test2)->getIsStaticObject()) {

                for (int c = 0; c < contactPair.getNbContactPoints(); c++) {
                    // Get the contact point
                    CollisionCallback::ContactPoint contactPoint = contactPair.getContactPoint(c);
                    float pen               = contactPoint.getPenetrationDepth();
                    glm::vec3 contactNormal = ReactMath::rp3dVecToGlm(contactPoint.getWorldNormal());

                    // Get the contact point on the first collider and convert it in world-space
                    glm::vec3 body1ContactPoint =
                        ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() *
                                                contactPoint.getLocalPointOnCollider1());
                    glm::vec3 body2ContactPoint =
                        ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() *
                                                contactPoint.getLocalPointOnCollider2());

                    std::cout << "(" << body1ContactPoint.x << ", " << body1ContactPoint.y << ", "
                              << body1ContactPoint.z << ")" << std::endl;

                    collisionResolution(test1, test2, pen, contactNormal, body1ContactPoint, body2ContactPoint);
                }

                glm::dvec3 lv1 =
                    PhysicsSystem::getInstance().getPhysicsBody(test1)->getLinearVelocity();
                PhysicsSystem::getInstance().getPhysicsBody(test1)->setLinearVelocity(-lv1);

                glm::dvec3 lv2 =
                    PhysicsSystem::getInstance().getPhysicsBody(test2)->getLinearVelocity();
                PhysicsSystem::getInstance().getPhysicsBody(test2)->setLinearVelocity(-lv2);

            }
        }

    }
}

void PhysicsResolution::collisionResolution(int body1, int body2, float pen, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint) {

    
    float coefficientOfRestitution = 0.6;

    glm::vec3 linearVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getLinearVelocity();
    glm::vec3 angularVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getAngularVelocity();
    glm::vec3 linearVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getLinearVelocity();
    glm::vec3 angularVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getAngularVelocity();

    glm::vec3 r1 = body1ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() + PhysicsSystem::getInstance().getPhysicsBody(body1)->getCentreOfMass());
    glm::vec3 r2 = body2ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() + PhysicsSystem::getInstance().getPhysicsBody(body2)->getCentreOfMass());

    PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() += contactNormal * ((pen / 2) * -1);
    PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() -= contactNormal * ((pen / 2) * -1);

        // Transfer of momentum

        //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
        // __________________________________________________________________________ * n̂
        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

        //  -(1 + ε) -(1 + e)
        float restitution = -(1.0 + coefficientOfRestitution);

        // (v⁻₁ - v⁻₂) (v-1 - v-2)
        glm::vec3 relativeVelocity = linearVelocity1 - linearVelocity2;

        //(r₁ x n̂) (r1 x n)
        auto r1cross = glm::cross(r1, contactNormal);

        //(r₂ x n̂) (r2 x n)
        auto r2cross = glm::cross(r2, contactNormal);

        // (m₁⁻¹ + m₂⁻¹) (m1-1 + m2-1)
        float combinedInverseMass = PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass() + PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

        //-(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
        float numerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1cross) - glm::dot(angularVelocity2, r2cross));

        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)
        float denominator = combinedInverseMass + (glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + glm::dot(r2cross, PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross));

        //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
        // __________________________________________________________________________ * n̂
        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

        // Transfer of momentum
        auto lambda = (numerator / denominator);

        // linear impulse
        auto linearImpulse = lambda * contactNormal;

        std::cout << lambda << std::endl;

        /*
        if (lambda < 0) {
            // v⁺₁ = v⁻₁
            linearVelocity1 += linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass();
            // v⁺₂ = v⁻₂
            linearVelocity2 -= linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

            angularVelocity1 = angularVelocity1 + (lambda * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor()) * r1cross;
            angularVelocity2 = angularVelocity2 - (lambda * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor()) * r2cross;
        }
        */
}
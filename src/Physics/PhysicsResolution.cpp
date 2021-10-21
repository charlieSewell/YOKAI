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

    glm::vec3 linearVelocity1 = glm::vec3(1, 0, 0);
    //glm::vec3 linearVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getLinearVelocity();
    glm::vec3 angularVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getAngularVelocity();
    glm::vec3 linearVelocity2 = glm::vec3(-1, 0, 0);
    //glm::vec3 linearVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getLinearVelocity();
    glm::vec3 angularVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getAngularVelocity();

    glm::vec3 r1 = body1ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() + PhysicsSystem::getInstance().getPhysicsBody(body1)->getCentreOfMass());
    glm::vec3 r2 = body2ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() + PhysicsSystem::getInstance().getPhysicsBody(body2)->getCentreOfMass());

    PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() += contactNormal * ((pen / 2) * -1);
    PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() -= contactNormal * ((pen / 2) * -1);

    float restitution = -(1.0 + coefficientOfRestitution);

    glm::vec3 relativeVelocity = linearVelocity1 - linearVelocity2;

    glm::vec3 r1cross = glm::cross(r1, contactNormal);

    glm::vec3 r2cross = glm::cross(r2, contactNormal);

    // CHECK THIS!
    float combinedInverseMass = PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass() + PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

    float numerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1cross) - glm::dot(angularVelocity2, r2cross));

    float denominator = combinedInverseMass + (glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + glm::dot(r2cross, PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross));


    // lambda
    auto lambda = (numerator / denominator);
    //std::cout << lambda << std::endl;

    // linear impulse
    auto linearImpulse = lambda * contactNormal;
    std::cout << "impulse - (" << linearImpulse.x << ", " << linearImpulse.y << ", " << linearImpulse.z << ")" << std::endl;

    std::cout << "linear - (" << (linearVelocity1 + (linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass())).x << ", " << (linearVelocity1 + (linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass())).y << ", " << (linearVelocity1 +(linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass())).z << std::endl;

    //TESTING
    //std::cout << "R1 - (" << r1.x << ", " << r1.y << ", " << r1.z << ")" << std::endl;
    //std::cout << "R2 - (" << r2.x << ", " << r2.y << ", " << r2.z << ")" << std::endl;
    //std::cout << restitution << std::endl;
    //std::cout << "RV - (" << relativeVelocity.x << ", " << relativeVelocity.y << ", " << relativeVelocity.z << ")" << std::endl;
    //std::cout << "R1cross - (" << r1cross.x << ", " << r1cross.y << ", " << r1cross.z << ")" << std::endl;
    //std::cout << "R2cross - (" << r2cross.x << ", " << r2cross.y << ", " << r2cross.z << ")" << std::endl; std::cout <<
    //std::cout << combinedInverseMass << std::endl;
    //std::cout << numerator << std::endl;
    //std::cout << denominator << std::endl;

    //DEMONINATOR ISSUE
    //glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross)
    //std::cout << glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) << std::endl;

    //(glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + glm::dot(r2cross, PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross))
    //std::cout << (glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + glm::dot(r2cross, PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross)) << std::endl;

    //INERTIA TENSOR
    //std::cout << PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor()[0][1] << std::endl;

    /*
    if (lambda < 0) {
        linearVelocity1 += linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass();
        linearVelocity2 -= linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

        angularVelocity1 = angularVelocity1 + (lambda * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor()) * r1cross;
        angularVelocity2 = angularVelocity2 - (lambda * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor()) * r2cross;
    }
    */
}
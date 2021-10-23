#include "PhysicsResolution.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/matrix.hpp"

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
    //std::cout << "Starting physics resolution" << std::endl;
    for (int p = 0; p < callbackData.getNbContactPairs(); p++) 
    {
        // Get the contact pair
        CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
        int test1                                  = contactPair.getCollider1()->getEntity().id;
        int test2                                  = contactPair.getCollider2()->getEntity().id;

        if (contactPair.getEventType() == CollisionCallback::ContactPair::EventType::ContactStart) {

            if (!PhysicsSystem::getInstance().getPhysicsBody(test1)->getIsStaticObject() &&
                !PhysicsSystem::getInstance().getPhysicsBody(test2)->getIsStaticObject()) {

                //std::cout << "com " << glm::to_string(PhysicsSystem::getInstance().getPhysicsBody(test1)->getCentreOfMass());

                /*
                std::cout << "getPosition 1 - ("
                          << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().x << ", "
                          << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().y << ", "
                          << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().z
                          << ")" << std::endl;
                */

                for (int c = 0; c < contactPair.getNbContactPoints(); c++) {
                    // Get the contact point
                    CollisionCallback::ContactPoint contactPoint = contactPair.getContactPoint(c);
                    double pen               = contactPoint.getPenetrationDepth();
                    glm::dvec3 contactNormal = ReactMath::rp3dVecToGlm(const_cast<rp3d::Vector3&>(contactPoint.getWorldNormal()));

                    // Get the contact point on the first collider and convert it in world-space
                    glm::dvec3 body1ContactPoint =
                        ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() *
                                                contactPoint.getLocalPointOnCollider1());
                    glm::dvec3 body2ContactPoint =
                        ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() *
                                                contactPoint.getLocalPointOnCollider2());

                    //std::cout << "b1 col - (" << body1ContactPoint.x << ", " << body1ContactPoint.y << ", " << body1ContactPoint.z << ")" << std::endl;
                    //std::cout << "b2 col - (" << body2ContactPoint.x << ", " << body2ContactPoint.y << ", " << body2ContactPoint.z << ")" << std::endl;

                    //std::cout << "CN (" << contactNormal.x << ", " << contactNormal.y << ", " << contactNormal.z << ")" << std::endl;
                    
                    std::cout
                        << "centreOfMass 1 - ("
                        << PhysicsSystem::getInstance().getPhysicsBody(test1)->getCentreOfMass().x
                        << ", "
                        << PhysicsSystem::getInstance().getPhysicsBody(test1)->getCentreOfMass().y
                        << ", "
                        << PhysicsSystem::getInstance().getPhysicsBody(test1)->getCentreOfMass().z
                        << ")" << std::endl;

                    std::cout
                        << "centreOfMass 2 - ("
                        << PhysicsSystem::getInstance().getPhysicsBody(test2)->getCentreOfMass().x
                        << ", "
                        << PhysicsSystem::getInstance().getPhysicsBody(test2)->getCentreOfMass().y
                        << ", "
                        << PhysicsSystem::getInstance().getPhysicsBody(test2)->getCentreOfMass().z
                        << ")" << std::endl;
                    /*
                    std::cout << "getPosition 1 - ("
                              << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().x
                              << ", "
                              << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().y
                              << ", "
                              << PhysicsSystem::getInstance().getPhysicsBody(test1)->GetPosition().z
                              << ")" << std::endl;
                              */
                    collisionResolution(test1, test2, pen, contactNormal, body1ContactPoint, body2ContactPoint);
                }
                /*
                glm::dvec3 lv1 =
                    PhysicsSystem::getInstance().getPhysicsBody(test1)->getLinearVelocity();
                PhysicsSystem::getInstance().getPhysicsBody(test1)->setLinearVelocity(-lv1);

                glm::dvec3 lv2 =
                    PhysicsSystem::getInstance().getPhysicsBody(test2)->getLinearVelocity();
                PhysicsSystem::getInstance().getPhysicsBody(test2)->setLinearVelocity(-lv2);
                */
            }
        }

    }
    //std::cout << "Ending physics resolution" << std::endl;
}

void PhysicsResolution::collisionResolution(int body1, int body2, double pen, glm::dvec3 contactNormal, glm::dvec3 body1ContactPoint, glm::dvec3 body2ContactPoint) {

    double coefficientOfRestitution = 0.6;

    glm::dvec3 linearVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getLinearVelocity();
    glm::dvec3 angularVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->getAngularVelocity();
    glm::dvec3 linearVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getLinearVelocity();
    glm::dvec3 angularVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->getAngularVelocity();

    glm::dvec3 r1 = body1ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body1)->getCentreOfMass());
    glm::dvec3 r2 = body2ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body2)->getCentreOfMass());

    double restitution = -(1.0 + coefficientOfRestitution);

    glm::dvec3 relativeVelocity = linearVelocity1 - linearVelocity2;

    glm::dvec3 r1cross = glm::cross(r1, contactNormal);

    glm::dvec3 r2cross = glm::cross(r2, contactNormal);

    double combinedInverseMass = PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass() + PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

    double numerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1cross) - glm::dot(angularVelocity2, r2cross));
    //glm::dvec3 numerator = (restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1cross) - glm::dot(angularVelocity2, r2cross))) * contactNormal;
    glm::dvec3 denominator = combinedInverseMass + ((r1cross * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + (r2cross * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross));

    //double testNumerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1cross) - glm::dot(angularVelocity2, r2cross));
    //double testDenominator = combinedInverseMass + (glm::dot(r1cross, PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor() * r1cross) + (glm::dot(r2cross, PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor() * r2cross)));
    
    glm::dvec3 lambda = numerator / denominator;

    // linear impulse
	glm::dvec3 linearImpulse = ((numerator * contactNormal) / denominator);

    //glm::dvec3 lambda = linearImpulse / contactNormal;
    //std::cout << lambda.x << ", " << lambda.y << ", " << lambda.z<< std::endl;

    // linear impulse
    //glm::dvec3 testLinearImpulse = lambda * contactNormal;
    //std::cout << "impulse - (" << linearImpulse.x << ", " << linearImpulse.y << ", " << linearImpulse.z << ")" << std::endl;
    
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

    //linearVelocity1 += testLinearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseMass();
    //linearVelocity2 -= testLinearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseMass();

    linearVelocity1 += linearImpulse / PhysicsSystem::getInstance().getPhysicsBody(body1)->getMass();
    linearVelocity2 -= linearImpulse / PhysicsSystem::getInstance().getPhysicsBody(body2)->getMass();

    angularVelocity1 = angularVelocity1 + (lambda * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor()) * r1cross;
    angularVelocity2 = angularVelocity2 - (lambda * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor()) * r2cross;

    // LINEAR IMPULSE USED INSTEAD OF LAMBDA
    //angularVelocity1 = angularVelocity1 + (linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body1)->getInverseInertiaTensor()) * r1cross;
    //angularVelocity2 = angularVelocity2 - (linearImpulse * PhysicsSystem::getInstance().getPhysicsBody(body2)->getInverseInertiaTensor()) * r2cross;

    std::cout << angularVelocity1.x << ", " << angularVelocity1.y << ", " << angularVelocity1.z << std::endl;
    std::cout << angularVelocity2.x << ", " << angularVelocity2.y << ", " << angularVelocity2.z << std::endl;

	PhysicsSystem::getInstance().SubmitLinearVelocity(body1, linearVelocity1);
	PhysicsSystem::getInstance().SubmitLinearVelocity(body2, linearVelocity2);

    PhysicsSystem::getInstance().SubmitAngularVelocity(body1, angularVelocity1);
    PhysicsSystem::getInstance().SubmitAngularVelocity(body2, angularVelocity2);
}
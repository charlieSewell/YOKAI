#include "PhysicsResolution.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/matrix.hpp"

void PhysicsResolution::onContact(const rp3d::CollisionCallback::CallbackData &callbackData) 
{   
    for (int p = 0; p < callbackData.getNbContactPairs(); p++) 
    {
        CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);

        int body1 = contactPair.getCollider1()->getEntity().id;
        int body2 = contactPair.getCollider2()->getEntity().id;

        CollisionCallback::ContactPair::EventType eventType = contactPair.getEventType();

        if ((!PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject() || !PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject())) 
        {
            for (int c = 0; c < contactPair.getNbContactPoints(); c++) 
            {
                CollisionCallback::ContactPoint contactPoint = contactPair.getContactPoint(c);
                double penetration = contactPoint.getPenetrationDepth();
                glm::dvec3 contactNormal = ReactMath::rp3dVecToGlm(const_cast<rp3d::Vector3&>(contactPoint.getWorldNormal()));

                // Get the contact point on the first collider and convert it in world-space
                glm::dvec3 body1ContactPoint = ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider1());
                glm::dvec3 body2ContactPoint = ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider2());

                //std::cout << "b1 col - (" << body1ContactPoint.x << ", " << body1ContactPoint.y << ", " << body1ContactPoint.z << ")" << std::endl;
                //std::cout << "b2 col - (" << body2ContactPoint.x << ", " << body2ContactPoint.y << ", " << body2ContactPoint.z << ")" << std::endl;

                //ResolvePenetration(body1, body2, penetration, contactNormal);
                //CollisionResolution(body1, body2, penetration, contactNormal, body1ContactPoint, body2ContactPoint, eventType);
            }
        }
    }
}

void PhysicsResolution::ResolvePenetration(int body1, int body2, double penetration, glm::dvec3 contactNormal) 
{
    if (!PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().getPhysicsBody(body1)->SetPosition(PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() + ((-(penetration / 2)) * contactNormal));
    }

    if (!PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().getPhysicsBody(body2)->SetPosition(PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() - ((-(penetration / 2)) * contactNormal));
    }
}

void PhysicsResolution::CollisionResolution(int body1, int body2, double penetration, glm::dvec3 contactNormal, glm::dvec3 body1ContactPoint, glm::dvec3 body2ContactPoint, CollisionCallback::ContactPair::EventType eventType) 
{
    double coefficientOfRestitution = 0.5;

    glm::dvec3 linearVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->GetLinearVelocity();
    glm::dvec3 angularVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->GetAngularVelocity();

    glm::dvec3 linearVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->GetLinearVelocity();
    glm::dvec3 angularVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->GetAngularVelocity();

    glm::dvec3 r1 = body1ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body1)->GetCentreOfMass());
    glm::dvec3 r2 = body2ContactPoint - (PhysicsSystem::getInstance().getPhysicsBody(body2)->GetCentreOfMass());

    double restitution = -(1.0 + coefficientOfRestitution);
    glm::dvec3 relativeVelocity = linearVelocity1 - linearVelocity2;
    double combinedInverseMass = PhysicsSystem::getInstance().getPhysicsBody(body1)->GetInverseMass() + PhysicsSystem::getInstance().getPhysicsBody(body2)->GetInverseMass();

    glm::dvec3 r1CrossNormal = glm::cross(r1, contactNormal);
    glm::dvec3 r2CrossNormal = glm::cross(r2, contactNormal);

    double lambdaNumerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1CrossNormal) - glm::dot(angularVelocity2, r2CrossNormal));
    //glm::dvec3 lambdaDenominator = combinedInverseMass + ((r1CrossNormal * PhysicsSystem::getInstance().getPhysicsBody(body1)->GetInverseInertiaTensor() * r1CrossNormal) + (r2CrossNormal * PhysicsSystem::getInstance().getPhysicsBody(body2)->GetInverseInertiaTensor() * r2CrossNormal));
    double lambdaDenominator = combinedInverseMass + (glm::dot(r1CrossNormal, PhysicsSystem::getInstance().getPhysicsBody(body1)->GetInverseInertiaTensor() * r1CrossNormal) + glm::dot(r2CrossNormal, PhysicsSystem::getInstance().getPhysicsBody(body2)->GetInverseInertiaTensor() * r2CrossNormal));

    //glm::dvec3 lambda = lambdaNumerator / lambdaDenominator;
    double lambda = lambdaNumerator / lambdaDenominator;

    if (lambda > 1) {
        //lambda = 1;
    }

    if (lambda < -1) {
        //lambda = -1;
    }

	//glm::dvec3 linearImpulse = ((lambdaNumerator * contactNormal) / lambdaDenominator);

    glm::dvec3 linearImpulse = lambda * contactNormal;

    if (lambda < 0) 
    {
        linearVelocity1 += linearImpulse / PhysicsSystem::getInstance().getPhysicsBody(body1)->GetMass();
        angularVelocity1 += (lambda * PhysicsSystem::getInstance().getPhysicsBody(body1)->GetInverseInertiaTensor()) * r1CrossNormal;

        linearVelocity2 -= linearImpulse / PhysicsSystem::getInstance().getPhysicsBody(body2)->GetMass();
        angularVelocity2 -= (lambda * PhysicsSystem::getInstance().getPhysicsBody(body2)->GetInverseInertiaTensor()) * r2CrossNormal;
    }

    if ((!PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject() && PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject()) || (PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject() && !PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject())) 
    {
        if (eventType == CollisionCallback::ContactPair::EventType::ContactStart) 
        {
            //ResolvePenetration(body1, body2, penetration, contactNormal);
            //linearVelocity1  = Damping(linearVelocity1);
            //linearVelocity2  = Damping(linearVelocity2);
            //angularVelocity1 = Damping(angularVelocity1);
            //angularVelocity2 = Damping(angularVelocity2);

            //std::cout << "\n";
            //std::cout << "Start L1 - (" << linearVelocity1.x << ", " << linearVelocity1.y << ", " << linearVelocity1.z << ")" << std::endl;
            //std::cout << "Start A1 - (" << angularVelocity1.x << ", " << angularVelocity1.y << ", " << angularVelocity1.z << ")" << std::endl;
        } 
        else if (eventType == CollisionCallback::ContactPair::EventType::ContactStay) 
        {
            //ResolvePenetration(body1, body2, penetration, contactNormal);
            linearVelocity1  = Damping(linearVelocity1);
            linearVelocity2  = Damping(linearVelocity2);
            angularVelocity1 = Damping(angularVelocity1);
            angularVelocity2 = Damping(angularVelocity2);

            //linearVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->GetLinearVelocity();
            //angularVelocity1 = PhysicsSystem::getInstance().getPhysicsBody(body1)->GetAngularVelocity();

            //linearVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->GetLinearVelocity();
            //angularVelocity2 = PhysicsSystem::getInstance().getPhysicsBody(body2)->GetAngularVelocity();

            //std::cout << "\n";
            //std::cout << "Lambda - " << lambda << std::endl;
            //std::cout << "Stay L1 - (" << linearVelocity1.x << ", " << linearVelocity1.y << ", " << linearVelocity1.z << ")" << std::endl;
            //std::cout << "Stay A1 - (" << angularVelocity1.x << ", " << angularVelocity1.y << ", " << angularVelocity1.z << ")" << std::endl;
            //std::cout << "\n";
            //std::cout << "L2 - (" << linearVelocity2.x << ", " << linearVelocity2.y << ", " << linearVelocity2.z << ")" << std::endl;
            //std::cout << "A2 - (" << angularVelocity2.x << ", " << angularVelocity2.y << ", " << angularVelocity2.z << ")" << std::endl;
        } 
    }

    if (!PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().SubmitLinearVelocity(body1, linearVelocity1);
        PhysicsSystem::getInstance().SubmitAngularVelocity(body1, angularVelocity1);
    }

    if (!PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().SubmitLinearVelocity(body2, linearVelocity2);
        PhysicsSystem::getInstance().SubmitAngularVelocity(body2, angularVelocity2);
    }
}

glm::dvec3 PhysicsResolution::Damping(glm::dvec3 velocity) 
{
    double damping = 0.95;

    velocity = velocity * damping; 

    return velocity;
}
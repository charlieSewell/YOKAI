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
                float penetration = contactPoint.getPenetrationDepth();
                glm::dvec3 contactNormal = ReactMath::rp3dVecToGlm(const_cast<rp3d::Vector3&>(contactPoint.getWorldNormal()));

                // Get the contact point on the first collider and convert it in world-space
                glm::dvec3 body1ContactPoint = ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider1());
                glm::dvec3 body2ContactPoint = ReactMath::rp3dVecToGlm(contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider2());

                //std::cout << "b1 col - (" << body1ContactPoint.x << ", " << body1ContactPoint.y << ", " << body1ContactPoint.z << ")" << std::endl;
                //std::cout << "b2 col - (" << body2ContactPoint.x << ", " << body2ContactPoint.y << ", " << body2ContactPoint.z << ")" << std::endl;

                CollisionResolution(body1, body2, penetration, contactNormal, body1ContactPoint, body2ContactPoint, eventType);
            }
        }
    }
}

void PhysicsResolution::ResolvePenetration(int body1, int body2, float penetration, glm::vec3 contactNormal) 
{
    if (!PhysicsSystem::getInstance().getPhysicsBody(body1)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().getPhysicsBody(body1)->SetPosition(PhysicsSystem::getInstance().getPhysicsBody(body1)->GetPosition() + ((-(penetration)) * contactNormal));
    }

    if (!PhysicsSystem::getInstance().getPhysicsBody(body2)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().getPhysicsBody(body2)->SetPosition(PhysicsSystem::getInstance().getPhysicsBody(body2)->GetPosition() - ((-(penetration)) * contactNormal));
    }
}

void PhysicsResolution::CollisionResolution(int body1, int body2, float penetration, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint, CollisionCallback::ContactPair::EventType eventType) 
{
    float coefficientOfRestitution = 0.6;

    CollisionBody* body1Ptr = PhysicsSystem::getInstance().getPhysicsBody(body1);
    CollisionBody* body2Ptr = PhysicsSystem::getInstance().getPhysicsBody(body2);

    glm::vec3 linearVelocity1 = body1Ptr->GetLinearVelocity();
    glm::vec3 angularVelocity1 = body1Ptr->GetAngularVelocity();

    glm::vec3 linearVelocity2 = body2Ptr->GetLinearVelocity();
    glm::vec3 angularVelocity2 = body2Ptr->GetAngularVelocity();

    glm::vec3 r1 = body1ContactPoint - (body1Ptr->GetPosition());
    glm::vec3 r2 = body2ContactPoint - (body2Ptr->GetPosition());

    ResolvePenetration(body1, body2, penetration, contactNormal);

    float restitution = -(1.0 + coefficientOfRestitution);
    glm::vec3 relativeVelocity = linearVelocity1 - linearVelocity2;
    float combinedInverseMass = body1Ptr->GetInverseMass() + body2Ptr->GetInverseMass();

    glm::vec3 r1CrossNormal = glm::cross(r1, contactNormal);
    glm::vec3 r2CrossNormal = glm::cross(r2, contactNormal);

    float lambdaNumerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1CrossNormal) - glm::dot(angularVelocity2, r2CrossNormal));
    //glm::dvec3 lambdaDenominator = combinedInverseMass + ((r1CrossNormal * PhysicsSystem::getInstance().getPhysicsBody(body1)->GetInverseInertiaTensor() * r1CrossNormal) + (r2CrossNormal * PhysicsSystem::getInstance().getPhysicsBody(body2)->GetInverseInertiaTensor() * r2CrossNormal));
    float lambdaDenominator = combinedInverseMass + (glm::dot(r1CrossNormal, body1Ptr->GetInverseInertiaTensor() * r1CrossNormal) + glm::dot(r2CrossNormal, body2Ptr->GetInverseInertiaTensor() * r2CrossNormal));

    //glm::dvec3 lambda = lambdaNumerator / lambdaDenominator;
    float lambda = lambdaNumerator / lambdaDenominator;


	//glm::dvec3 linearImpulse = ((lambdaNumerator * contactNormal) / lambdaDenominator);

    glm::vec3 linearImpulse = lambda * contactNormal;

    if (lambda < 0) 
    {
        linearVelocity1 += linearImpulse / body1Ptr->GetMass();
        angularVelocity1 += (lambda * body1Ptr->GetInverseInertiaTensor()) * r1CrossNormal;

        linearVelocity2 -= linearImpulse / body2Ptr->GetMass();
        angularVelocity2 -= (lambda * body2Ptr->GetInverseInertiaTensor()) * r2CrossNormal;

        if (!body1Ptr->GetIsStaticObject()) {
            body1Ptr->SetLinearVelocity(linearVelocity1);
            body1Ptr->SetAngularVelocity(angularVelocity1);
        }

        if (!body2Ptr->GetIsStaticObject()) {
            body2Ptr->SetLinearVelocity(linearVelocity2);
            body2Ptr->SetAngularVelocity(angularVelocity2);
        }
    }
}

glm::vec3 PhysicsResolution::Damping(glm::vec3 velocity) 
{
    float damping = 0.8;

    velocity = velocity * damping; 

    return velocity;
}
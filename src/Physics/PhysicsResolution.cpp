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

        if ((!PhysicsSystem::getInstance().GetPhysicsBody(body1)->GetIsStaticObject() || !PhysicsSystem::getInstance().GetPhysicsBody(body2)->GetIsStaticObject())) 
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

                ResolvePenetration(body1, body2, penetration, contactNormal);
                CollisionResolution(body1, body2, penetration, contactNormal, body1ContactPoint, body2ContactPoint, eventType);
            }
        }
    }
}

void PhysicsResolution::ResolvePenetration(int body1, int body2, float penetration, glm::vec3 contactNormal) 
{
    //Resolves the penetration of non static objects prior to resolution, using the penetration depth and contact plane normal
    if (!PhysicsSystem::getInstance().GetPhysicsBody(body1)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().GetPhysicsBody(body1)->SetPosition(PhysicsSystem::getInstance().GetPhysicsBody(body1)->GetPosition() + ((-(penetration/2)) * contactNormal));
    }

    if (!PhysicsSystem::getInstance().GetPhysicsBody(body2)->GetIsStaticObject()) 
    {
        PhysicsSystem::getInstance().GetPhysicsBody(body2)->SetPosition(PhysicsSystem::getInstance().GetPhysicsBody(body2)->GetPosition() - ((-(penetration/2)) * contactNormal));
    }
}

void PhysicsResolution::CollisionResolution(int body1, int body2, float penetration, glm::vec3 contactNormal, glm::vec3 body1ContactPoint, glm::vec3 body2ContactPoint, CollisionCallback::ContactPair::EventType eventType) 
{
    //Coefficient of restitution (Changes elasticity of collisions)
    float coefficientOfRestitution = 0.6;

    //Pointers to collision bodies
    CollisionBody* body1Ptr = PhysicsSystem::getInstance().GetPhysicsBody(body1);
    CollisionBody* body2Ptr = PhysicsSystem::getInstance().GetPhysicsBody(body2);

    //Linear and Angular velocities
    glm::vec3 linearVelocity1 = body1Ptr->GetLinearVelocity();
    glm::vec3 angularVelocity1 = body1Ptr->GetAngularVelocity();

    glm::vec3 linearVelocity2 = body2Ptr->GetLinearVelocity();
    glm::vec3 angularVelocity2 = body2Ptr->GetAngularVelocity();

    //Distance from the contact point to centre of mass (Middle of object due to uniform distribution of mass)
    glm::vec3 r1 = body1ContactPoint - (body1Ptr->GetPosition());
    glm::vec3 r2 = body2ContactPoint - (body2Ptr->GetPosition());

    //Restitution numerator value
    float restitution = -(1.0 + coefficientOfRestitution);
    //Relative linear velocity between the two objects
    glm::vec3 relativeVelocity = linearVelocity1 - linearVelocity2;
    //Sum of the inverse mass for both bodies
    float combinedInverseMass = body1Ptr->GetInverseMass() + body2Ptr->GetInverseMass();

    //Cross product of r1/r2 and contact normal
    glm::vec3 r1CrossNormal = glm::cross(r1, contactNormal);
    glm::vec3 r2CrossNormal = glm::cross(r2, contactNormal);

    //Numerator and denominator for lambda equation

    float lambdaNumerator = restitution * (glm::dot(contactNormal, relativeVelocity) + glm::dot(angularVelocity1, r1CrossNormal) - glm::dot(angularVelocity2, r2CrossNormal));
    float lambdaDenominator = combinedInverseMass + (glm::dot(r1CrossNormal, body1Ptr->GetInverseInertiaTensor() * r1CrossNormal) + glm::dot(r2CrossNormal, body2Ptr->GetInverseInertiaTensor() * r2CrossNormal));

    //Lambda scalar
    float lambda = lambdaNumerator / lambdaDenominator;
    //Collision Impulse
    glm::vec3 collisionImpulse = lambda * contactNormal;

    if (lambda < 0) 
    {
        //Calculate new linear and angular velocities

        //Linear Velocity Equation
        // V1(+) = V1(-) + (Λ / m1)

        //Angular Velocity Equation
        // W1(+) = W1(-) + J1(-1)(r1 x n) 

        linearVelocity1 += collisionImpulse / body1Ptr->GetMass();
        angularVelocity1 += (lambda * body1Ptr->GetInverseInertiaTensor()) * r1CrossNormal;

        linearVelocity2 -= collisionImpulse / body2Ptr->GetMass();
        angularVelocity2 -= (lambda * body2Ptr->GetInverseInertiaTensor()) * r2CrossNormal;

        //Set new velocity values for non static bodies
        if (!body1Ptr->GetIsStaticObject()) 
        {
            body1Ptr->SetLinearVelocity(linearVelocity1);
            body1Ptr->SetAngularVelocity(angularVelocity1);
        }

        if (!body2Ptr->GetIsStaticObject()) 
        {
            body2Ptr->SetLinearVelocity(linearVelocity2);
            body2Ptr->SetAngularVelocity(angularVelocity2);
        }
    }
}
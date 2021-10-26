#include "CollisionBody.hpp"
#include "ReactMath.hpp"
#include "glm/gtx/string_cast.hpp"

void CollisionBody::CreateBody(int gameObjID,rp3d::PhysicsWorld* physicsWorld,glm::vec3 position,glm::quat orientation)
{
    gameObjectID = gameObjID;
    rp3d::Transform temp(ReactMath::glmVecToRP3d(position), ReactMath::glmQuatToRP3d(orientation));
    m_body = physicsWorld->createCollisionBody(temp);
}
void CollisionBody::DeleteBody(rp3d::PhysicsWorld* physicsWorld,rp3d::PhysicsCommon &physicsCommon)
{
    physicsWorld->destroyCollisionBody(m_body);
    shape->DeleteShape(physicsCommon);
}
void CollisionBody::SetPosition(glm::dvec3 position){
    m_position = position;
    rp3d::Transform currTransform = m_body->getTransform();
    currTransform.setPosition(ReactMath::glmVecToRP3d(position));
    m_body->setTransform(currTransform);
    
}
void CollisionBody::SetOrientation(glm::quat orientation)
{
    rp3d::Transform currTransform = m_body->getTransform();
    currTransform.setOrientation(ReactMath::glmQuatToRP3d(orientation));
    m_body->setTransform(currTransform);
}
glm::quat CollisionBody::GetOrientation()
{
    rp3d::Quaternion temp = m_body->getTransform().getOrientation();
    return ReactMath::rp3dQuatToGlm(temp);
}
glm::dvec3 CollisionBody::GetPosition()
{
    rp3d::Vector3 temp = m_body->getTransform().getPosition();
    //return ReactMath::rp3dVecToGlmD(temp);
    return m_position;
}

void CollisionBody::AddCollisionShape(ReactShape* shapeToInsert) 
{
    shape = shapeToInsert;
    m_collider = m_body->addCollider(shape->getCollisionShape(),rp3d::Transform::identity());

}

void CollisionBody::SetFrictionCoefficient(float friction)
{
    m_collider->getMaterial().setFrictionCoefficient(friction);
}

void CollisionBody::SetRollingResistance(float resistance)
{
    m_collider->getMaterial().setRollingResistance(resistance);
}

void CollisionBody::SetMass(double m) 
{
    m_mass = m;
}

double CollisionBody::GetMass() 
{
    return m_mass;
}

double CollisionBody::GetInverseMass() 
{
    return 1.0 / m_mass;
}

void CollisionBody::SetCentreOfMass(glm::dvec3 com) 
{
    m_centreOfMass = com;
}

glm::dvec3 CollisionBody::GetCentreOfMass() 
{
    return m_centreOfMass;
}

void CollisionBody::SetInertiaTensor(glm::dmat3x3 it) 
{
    m_inertiaTensor = it;
}

glm::dmat3x3 CollisionBody::GetInertiaTensor() 
{
    return m_inertiaTensor;
}

glm::dmat3x3 CollisionBody::GetInverseInertiaTensor() 
{
    return glm::inverse(m_inertiaTensor);
}

void CollisionBody::SetLinearVelocity(glm::dvec3 lv) 
{
    m_linearVelocity = lv;
}

glm::dvec3 CollisionBody::GetLinearVelocity() 
{
    return m_linearVelocity;
}

void CollisionBody::SetAngularVelocity(glm::dvec3 av) 
{
    m_angularVelocity = av;
}

glm::dvec3 CollisionBody::GetAngularVelocity() 
{
    return m_angularVelocity;
}

bool CollisionBody::GetIsStaticObject() 
{
    return m_staticObject;
}

void CollisionBody::SetIsStaticObject(bool s) 
{
    m_staticObject = s;
}

void CollisionBody::SetGravityAffected(bool g) 
{
    m_gravityAffected = g;
}

bool CollisionBody::GetGravityAffected() 
{
    return m_gravityAffected;
}

glm::mat4 CollisionBody::GetTransform() 
{
    rp3d::Transform temp = m_body->getTransform();
    return ReactMath::rp3dMat4ToGlm(temp);
}

void CollisionBody::SetTransform(glm::mat4 transform) 
{

}

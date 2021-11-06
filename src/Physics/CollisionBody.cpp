#include "CollisionBody.hpp"
#include "ReactMath.hpp"
#include "glm/gtx/string_cast.hpp"

void CollisionBody::CreateBody(int gameObjID,rp3d::PhysicsWorld* physicsWorld,glm::vec3 position,glm::quat orientation)
{
    m_gameObjectID = gameObjID;
    rp3d::Transform temp(ReactMath::glmVecToRP3d(position), ReactMath::glmQuatToRP3d(orientation));
    m_body = physicsWorld->createCollisionBody(temp);
}
void CollisionBody::DeleteBody(rp3d::PhysicsWorld* physicsWorld,rp3d::PhysicsCommon &physicsCommon)
{
    physicsWorld->destroyCollisionBody(m_body);
    m_shape->DeleteShape(physicsCommon);
}
void CollisionBody::SetPosition(glm::vec3 position){
    m_position = position;
}
void CollisionBody::SetOrientation(glm::quat orientation)
{
    m_orientation = orientation;
}
glm::quat CollisionBody::GetOrientation()
{
    rp3d::Quaternion temp = m_body->getTransform().getOrientation();
    return ReactMath::rp3dQuatToGlm(temp);
}
glm::vec3 CollisionBody::GetPosition()
{
    rp3d::Vector3 temp = m_body->getTransform().getPosition();
    return m_position;
}

void CollisionBody::AddCollisionShape(ReactShape* shapeToInsert) 
{
    m_shape = shapeToInsert;
    m_collider = m_body->addCollider(m_shape->getCollisionShape(),rp3d::Transform::identity());

}

void CollisionBody::SetFrictionCoefficient(float friction)
{
    m_collider->getMaterial().setFrictionCoefficient(friction);
}

void CollisionBody::SetRollingResistance(float resistance)
{
    m_collider->getMaterial().setRollingResistance(resistance);
}

void CollisionBody::SetMass(float m) 
{
    m_mass = m;
}

float CollisionBody::GetMass() 
{
    return m_mass;
}

float CollisionBody::GetInverseMass() 
{
    return 1.0 / m_mass;
}

void CollisionBody::SetCentreOfMass(glm::vec3 com) 
{
    m_centreOfMass = com;
}

glm::vec3 CollisionBody::GetCentreOfMass() 
{
    return m_centreOfMass;
}

void CollisionBody::SetInertiaTensor(glm::mat3x3 it) 
{
    m_inertiaTensor = it;
    m_inverseInertiaTensor = glm::inverse(m_inertiaTensor);
}

glm::mat3x3 CollisionBody::GetInertiaTensor() 
{
    return m_inertiaTensor;
}

glm::mat3x3 CollisionBody::GetInverseInertiaTensor() 
{
    return m_inverseInertiaTensor;
}

void CollisionBody::SetLinearVelocity(glm::vec3 lv) 
{
    m_linearVelocity = lv;
}

glm::vec3 CollisionBody::GetLinearVelocity() 
{
    return m_linearVelocity;
}

void CollisionBody::SetAngularVelocity(glm::vec3 av) 
{
    m_angularVelocity = av;
}

glm::vec3 CollisionBody::GetAngularVelocity() 
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

void CollisionBody::UpdateBody() 
{
    rp3d::Transform temp = rp3d::Transform(ReactMath::glmVecToRP3d(m_position), ReactMath::glmQuatToRP3d(m_orientation));
    m_body->setTransform(temp);
}

void CollisionBody::SetCollisionCategory(unsigned short category)
 {
     m_collider->setCollisionCategoryBits(category);
}
void CollisionBody::SetCollisionMaskBits(unsigned short maskBits)
{
     m_collider->setCollideWithMaskBits(maskBits);
}

#include "CollisionBody.hpp"
#include "ReactMath.hpp"

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
void CollisionBody::SetPosition(glm::vec3 position){
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
glm::vec3 CollisionBody::GetPosition()
{
    rp3d::Vector3 temp = m_body->getTransform().getPosition();
    return ReactMath::rp3dVecToGlm(temp);
}

void CollisionBody::AddCollisionShape(ReactShape* shapeToInsert) {
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
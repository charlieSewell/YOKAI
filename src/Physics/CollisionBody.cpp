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
    //std::cout << "changing position" << glm::to_string(m_position) << std::endl;
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

void CollisionBody::setMass(double m) {
    mass = m;
}

double CollisionBody::getMass() {
    return mass;
}

double CollisionBody::getInverseMass() {
    return 1.0 / mass;
}

void CollisionBody::setCentreOfMass(glm::dvec3 com) {
    centreOfMass = com;
}

glm::dvec3 CollisionBody::getCentreOfMass() {
    return centreOfMass;
}

void CollisionBody::setInertiaTensor(glm::dmat3x3 it) {
    inertiaTensor = it;
}

glm::dmat3x3 CollisionBody::getInertiaTensor() {
    return inertiaTensor;
}

glm::dmat3x3 CollisionBody::getInverseInertiaTensor() {
    return glm::inverse(inertiaTensor);
}

void CollisionBody::setLinearVelocity(glm::dvec3 lv) {
    linearVelocity = lv;
}

glm::dvec3 CollisionBody::getLinearVelocity() {
    return linearVelocity;
}

void CollisionBody::setAngularVelocity(glm::dvec3 av) {
    angularVelocity = av;
}

glm::dvec3 CollisionBody::getAngularVelocity() {
    return angularVelocity;
}

void CollisionBody::setTorque(glm::dvec3 t) {
    torque = t;
}

glm::dvec3 CollisionBody::getTorque() {
    return torque;
}

void CollisionBody::setForce(glm::dvec3 f) {
    force = f;
}

glm::dvec3 CollisionBody::getForce() {
    return force;
}

bool CollisionBody::getIsStaticObject() {
    return staticObject;
}

void CollisionBody::setIsStaticObject(bool s) {
    staticObject = s;
}

void CollisionBody::setGravityAffected(bool g) {
    gravityAffected = g;
}

bool CollisionBody::getGravityAffected() {
    return gravityAffected;
}
void CollisionBody::SetCollisionCategory(unsigned short category)
 {
     m_collider->setCollisionCategoryBits(category);
}
void CollisionBody::SetCollisionMaskBits(unsigned short maskBits)
{
     m_collider->setCollideWithMaskBits(maskBits);
}
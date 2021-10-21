#include "BoxCollider.hpp"

BoxCollider::BoxCollider(GameObject* parent) : Component(parent){}

void BoxCollider::Start()
{
    //extents = glm::vec3(1,1,1);
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    colliderID = PhysicsSystem::getInstance().addAABB(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),extents.x,extents.y,extents.z);
}
void BoxCollider::SetExtents(glm::vec3 extent)
{
   extents = extent;
}

void BoxCollider::SetOrientation(glm::quat orientation)
{
	PhysicsSystem::getInstance().getPhysicsBody(colliderID)->SetOrientation(orientation);
}

void BoxCollider::SetExtents(float x,float y, float z)
{
   extents = glm::vec3(x,y,z);
}

void BoxCollider::Update(float deltaTime)
{
	//std::cout << " " << m_parent->GetComponent<Transform>()->getPosition().x << " " << m_parent->GetComponent<Transform>()->getPosition().y << " " << m_parent->GetComponent<Transform>()->getPosition().z << std::endl;
}

void BoxCollider::SetPosition(glm::vec3 newPosition) 
{
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->SetPosition(newPosition);
}

void BoxCollider::setMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setMass(m);
}

double BoxCollider::getMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getMass();
}

double BoxCollider::getInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInverseMass();
}

void BoxCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setCentreOfMass(com);
}

glm::dvec3 BoxCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getCentreOfMass();
}

void BoxCollider::setInertiaTensor() {
    
    glm::mat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, getMass());
    
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setInertiaTensor(temp);
}

glm::dmat3x3 BoxCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInertiaTensor();
}

glm::dmat3x3 BoxCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInverseInertiaTensor();
}

void BoxCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setLinearVelocity(lv);
}

glm::dvec3 BoxCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getLinearVelocity();
}

void BoxCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setAngularVelocity(av);
}

glm::dvec3 BoxCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getAngularVelocity();
}

void BoxCollider::setTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setTorque(t);
}

glm::dvec3 BoxCollider::getTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getTorque();
}

void BoxCollider::setForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setForce(f);
}

glm::dvec3 BoxCollider::getForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getForce();
}

void BoxCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setIsStaticObject(s);
}

bool BoxCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getIsStaticObject();
}

void BoxCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setGravityAffected(g);
}

bool BoxCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getGravityAffected();
}

glm::vec3 BoxCollider::getExtents() {
    return extents;
}

void BoxCollider::initInertiaTensor() {
    
    glm::mat3x3 temp;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = 0;
        }
    }
}
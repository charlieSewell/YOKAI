#include "ConcaveCollider.hpp"

ConcaveCollider::ConcaveCollider(GameObject* parent) : Component(parent){}

void ConcaveCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
	m_colliderID = PhysicsSystem::getInstance().addConcaveShape(3,m_parent->GetComponent<Transform>().get(),m_parent->GetComponent<DrawableEntity>()->GetModelID());
}

void ConcaveCollider::Update(float deltaTime)
{

}

void ConcaveCollider::setMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setMass(m);
}

double ConcaveCollider::getMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getMass();
}

double ConcaveCollider::getInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseMass();
}

void ConcaveCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setCentreOfMass(com);
}

glm::dvec3 ConcaveCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getCentreOfMass();
}

void ConcaveCollider::setInertiaTensor(glm::dmat3x3 it) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setInertiaTensor(it);
}

glm::dmat3x3 ConcaveCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInertiaTensor();
}

glm::dmat3x3 ConcaveCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseInertiaTensor();
}

void ConcaveCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setLinearVelocity(lv);
}

glm::dvec3 ConcaveCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getLinearVelocity();
}

void ConcaveCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setAngularVelocity(av);
}

glm::dvec3 ConcaveCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getAngularVelocity();
}

void ConcaveCollider::setTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setTorque(t);
}

glm::dvec3 ConcaveCollider::getTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getTorque();
}

void ConcaveCollider::setForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setForce(f);
}

glm::dvec3 ConcaveCollider::getForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getForce();
}

void ConcaveCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setIsStaticObject(s);
}

bool ConcaveCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getIsStaticObject();
}

void ConcaveCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setGravityAffected(g);
}

bool ConcaveCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getGravityAffected();
}
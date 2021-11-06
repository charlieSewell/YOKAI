#include "ConcaveCollider.hpp"

ConcaveCollider::ConcaveCollider(GameObject* parent) : Component(parent){}

void ConcaveCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
	m_colliderID = PhysicsSystem::getInstance().AddConcaveShape(3,m_parent->GetComponent<Transform>().get(),m_parent->GetComponent<DrawableEntity>()->GetModelID());
}

void ConcaveCollider::Update(float deltaTime)
{

}

void ConcaveCollider::setMass(double m) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetMass(m);
}

double ConcaveCollider::getMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetMass();
}

double ConcaveCollider::getInverseMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseMass();
}

void ConcaveCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::dvec3 ConcaveCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void ConcaveCollider::setInertiaTensor(glm::dmat3x3 it) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetInertiaTensor(it);
}

glm::dmat3x3 ConcaveCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::dmat3x3 ConcaveCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void ConcaveCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::dvec3 ConcaveCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void ConcaveCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::dvec3 ConcaveCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetAngularVelocity();
}

void ConcaveCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetIsStaticObject(s);
}

bool ConcaveCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetIsStaticObject();
}

void ConcaveCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetGravityAffected(g);
}

bool ConcaveCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetGravityAffected();
}
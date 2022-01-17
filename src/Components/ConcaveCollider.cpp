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

void ConcaveCollider::setMass(float m) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetMass(m);
}

float ConcaveCollider::getMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetMass();
}

float ConcaveCollider::getInverseMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseMass();
}

void ConcaveCollider::setCentreOfMass(glm::vec3 com) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::vec3 ConcaveCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void ConcaveCollider::setInertiaTensor(glm::mat3x3 it) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetInertiaTensor(it);
}

glm::mat3x3 ConcaveCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::mat3x3 ConcaveCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void ConcaveCollider::setLinearVelocity(glm::vec3 lv) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::vec3 ConcaveCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void ConcaveCollider::setAngularVelocity(glm::vec3 av) {
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::vec3 ConcaveCollider::getAngularVelocity() {
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
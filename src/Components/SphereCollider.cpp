#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::SetRadius(double radius)
{
	m_radius = radius;
}
void SphereCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
	}
    m_colliderID = PhysicsSystem::getInstance().addSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(), m_radius);
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
}

void SphereCollider::SetPosition(glm::vec3 newPosition)
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(newPosition);
}

unsigned int SphereCollider::GetColliderID()
{
	return m_colliderID;
}

void SphereCollider::setMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setMass(m);
}

double SphereCollider::getMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getMass();
}

double SphereCollider::getInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseMass();
}

void SphereCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setCentreOfMass(com);
}

glm::dvec3 SphereCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getCentreOfMass();
}

void SphereCollider::setInertiaTensor(glm::dmat3x3 it) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setInertiaTensor(it);
}

glm::dmat3x3 SphereCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInertiaTensor();
}

glm::dmat3x3 SphereCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseInertiaTensor();
}

void SphereCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setLinearVelocity(lv);
}

glm::dvec3 SphereCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getLinearVelocity();
}

void SphereCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setAngularVelocity(av);
}

glm::dvec3 SphereCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getAngularVelocity();
}

void SphereCollider::setTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setTorque(t);
}

glm::dvec3 SphereCollider::getTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getTorque();
}

void SphereCollider::setForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setForce(f);
}

glm::dvec3 SphereCollider::getForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getForce();
}

void SphereCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setIsStaticObject(s);
}

bool SphereCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getIsStaticObject();
}

void SphereCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setGravityAffected(g);
}

bool SphereCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getGravityAffected();
}
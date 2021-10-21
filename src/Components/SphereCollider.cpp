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
    colliderID = PhysicsSystem::getInstance().addSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(), m_radius);
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
}

void SphereCollider::SetPosition(glm::vec3 newPosition)
{
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->SetPosition(newPosition);
}

void SphereCollider::setMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setMass(m);
}

double SphereCollider::getMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getMass();
}

double SphereCollider::getInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInverseMass();
}

void SphereCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setCentreOfMass(com);
}

glm::dvec3 SphereCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getCentreOfMass();
}

void SphereCollider::setInertiaTensor(glm::dmat3x3 it) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setInertiaTensor(it);
}

glm::dmat3x3 SphereCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInertiaTensor();
}

glm::dmat3x3 SphereCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getInverseInertiaTensor();
}

void SphereCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setLinearVelocity(lv);
}

glm::dvec3 SphereCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getLinearVelocity();
}

void SphereCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setAngularVelocity(av);
}

glm::dvec3 SphereCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getAngularVelocity();
}

void SphereCollider::setTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setTorque(t);
}

glm::dvec3 SphereCollider::getTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getTorque();
}

void SphereCollider::setForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setForce(f);
}

glm::dvec3 SphereCollider::getForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getForce();
}

void SphereCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setIsStaticObject(s);
}

bool SphereCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getIsStaticObject();
}

void SphereCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setGravityAffected(g);
}

bool SphereCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getGravityAffected();
}
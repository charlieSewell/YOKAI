#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }

    m_colliderID = PhysicsSystem::getInstance().addSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(), m_radius);
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
    SetCentreOfMass(GetPosition());
}

void SphereCollider::SetOrientation(glm::quat orientation) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(orientation);
}

void SphereCollider::SetPosition(glm::dvec3 newPosition) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(newPosition);
}

glm::dvec3 SphereCollider::GetPosition() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetPosition();
}

glm::quat SphereCollider::GetOrientation() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetOrientation();
}

int SphereCollider::GetColliderID() {
    return m_colliderID;
}

void SphereCollider::Update(float deltaTime) {
    // glm::dvec3 lv = getLinearVelocity();
    // std::cout << glm::to_string(GetPosition()) << std::endl;
    Translate(GetLinearVelocity() * static_cast<double>(deltaTime));
    Rotate(GetAngularVelocity(), deltaTime);
    SetCentreOfMass(GetPosition());
}

void SphereCollider::SetMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setMass(m);
}

double SphereCollider::GetMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getMass();
}

double SphereCollider::GetInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseMass();
}

void SphereCollider::SetCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setCentreOfMass(com);
}

glm::dvec3 SphereCollider::GetCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getCentreOfMass();
}

void SphereCollider::SetInertiaTensor() {

    glm::dmat3x3 temp = YokaiPhysics::SphereInertiaTensor(m_radius, GetMass());

    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setInertiaTensor(temp);
}

glm::dmat3x3 SphereCollider::GetInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInertiaTensor();
}

glm::dmat3x3 SphereCollider::GetInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseInertiaTensor();
}

void SphereCollider::SetLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setLinearVelocity(lv);
}

glm::dvec3 SphereCollider::GetLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getLinearVelocity();
}

void SphereCollider::SetAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setAngularVelocity(av);
}

glm::dvec3 SphereCollider::GetAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getAngularVelocity();
}

void SphereCollider::SetTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setTorque(t);
}

glm::dvec3 SphereCollider::GetTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getTorque();
}

void SphereCollider::SetForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setForce(f);
}

glm::dvec3 SphereCollider::GetForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getForce();
}

void SphereCollider::SetIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setIsStaticObject(s);
}

bool SphereCollider::GetIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getIsStaticObject();
}

void SphereCollider::SetGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setGravityAffected(g);
}

bool SphereCollider::GetGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getGravityAffected();
}

void SphereCollider::SetRadius(double radius) {
    m_radius = radius;
}

double SphereCollider::GetRadius() {
    return m_radius;
}

void SphereCollider::Translate(glm::dvec3 position) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(position + GetPosition());
}

void SphereCollider::Rotate(glm::dvec3 angVelocity, float deltaTime) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));
}
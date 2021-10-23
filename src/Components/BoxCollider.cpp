#include "BoxCollider.hpp"
#include "glm/gtx/string_cast.hpp"

BoxCollider::BoxCollider(GameObject* parent) : Component(parent){}

void BoxCollider::Start()
{
    //extents = glm::vec3(1,1,1);
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
	m_colliderID = PhysicsSystem::getInstance().addAABB(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),extents.x,extents.y,extents.z);
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
    SetCentreOfMass(GetPosition());
}
void BoxCollider::SetExtents(glm::vec3 extent)
{
   extents = extent;
}

void BoxCollider::SetOrientation(glm::quat orientation)
{
	PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(orientation);
}

void BoxCollider::SetExtents(float x,float y, float z)
{
   extents = glm::dvec3(x,y,z);
}

void BoxCollider::SetPosition(glm::dvec3 newPosition)
{
	PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(newPosition);
}

glm::dvec3 BoxCollider::GetPosition() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetPosition();
}

glm::quat BoxCollider::GetOrientation() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetOrientation();
}

int BoxCollider::GetColliderID()
{
	return m_colliderID;
}

void BoxCollider::Update(float deltaTime)
{
    //glm::dvec3 lv = getLinearVelocity();
    //std::cout << glm::to_string(GetPosition()) << std::endl;
    Translate(GetLinearVelocity() * static_cast<double>(deltaTime));
    Rotate(GetAngularVelocity(), deltaTime);
    SetCentreOfMass(GetPosition());
}

void BoxCollider::SetMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setMass(m);
}

double BoxCollider::GetMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getMass();
}

double BoxCollider::GetInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseMass();
}

void BoxCollider::SetCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setCentreOfMass(com);
}

glm::dvec3 BoxCollider::GetCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getCentreOfMass();
}

void BoxCollider::SetInertiaTensor() {
    
    glm::dmat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, GetMass());
    
    //std::cout << "extent x " << extents.x << std::endl;

    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setInertiaTensor(temp);
}

glm::dmat3x3 BoxCollider::GetInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInertiaTensor();
}

glm::dmat3x3 BoxCollider::GetInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseInertiaTensor();
}

void BoxCollider::SetLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setLinearVelocity(lv);
}

glm::dvec3 BoxCollider::GetLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getLinearVelocity();
}

void BoxCollider::SetAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setAngularVelocity(av);
}

glm::dvec3 BoxCollider::GetAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getAngularVelocity();
}

void BoxCollider::SetTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setTorque(t);
}

glm::dvec3 BoxCollider::GetTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getTorque();
}

void BoxCollider::SetForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setForce(f);
}

glm::dvec3 BoxCollider::GetForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getForce();
}

void BoxCollider::SetIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setIsStaticObject(s);
}

bool BoxCollider::GetIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getIsStaticObject();
}

void BoxCollider::SetGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setGravityAffected(g);
}

bool BoxCollider::GetGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getGravityAffected();
}

glm::dvec3 BoxCollider::GetExtents() {
    return extents;
}

void BoxCollider::Translate(glm::dvec3 position) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(position + GetPosition());
}

void BoxCollider::Rotate(glm::dvec3 angVelocity, float deltaTime) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(GetOrientation() + glm::quat(0.0, angVelocity) * GetOrientation() * deltaTime);
}


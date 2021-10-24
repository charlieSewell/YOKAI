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
    setCentreOfMass(GetPosition());
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

int BoxCollider::GetColliderID()
{
	return m_colliderID;
}

void BoxCollider::Update(float deltaTime)
{
    glm::dvec3 lv = getLinearVelocity();
    //std::cout << glm::to_string(GetPosition()) << std::endl;
    translate(getLinearVelocity() * static_cast<double>(deltaTime));
    setCentreOfMass(GetPosition());
}

void BoxCollider::setMass(double m) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setMass(m);
}

double BoxCollider::getMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getMass();
}

double BoxCollider::getInverseMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseMass();
}

void BoxCollider::setCentreOfMass(glm::dvec3 com) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setCentreOfMass(com);
}

glm::dvec3 BoxCollider::getCentreOfMass() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getCentreOfMass();
}

void BoxCollider::setInertiaTensor() {
    
    glm::dmat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, getMass());
    
    //std::cout << "extent x " << extents.x << std::endl;

    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setInertiaTensor(temp);
}

glm::dmat3x3 BoxCollider::getInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInertiaTensor();
}

glm::dmat3x3 BoxCollider::getInverseInertiaTensor() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getInverseInertiaTensor();
}

void BoxCollider::setLinearVelocity(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setLinearVelocity(lv);
}

glm::dvec3 BoxCollider::getLinearVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getLinearVelocity();
}

void BoxCollider::setAngularVelocity(glm::dvec3 av) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setAngularVelocity(av);
}

glm::dvec3 BoxCollider::getAngularVelocity() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getAngularVelocity();
}

void BoxCollider::setTorque(glm::dvec3 t) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setTorque(t);
}

glm::dvec3 BoxCollider::getTorque() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getTorque();
}

void BoxCollider::setForce(glm::dvec3 f) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setForce(f);
}

glm::dvec3 BoxCollider::getForce() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getForce();
}

void BoxCollider::setIsStaticObject(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setIsStaticObject(s);
}

bool BoxCollider::getIsStaticObject() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getIsStaticObject();
}

void BoxCollider::setGravityAffected(bool g) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->setGravityAffected(g);
}

bool BoxCollider::getGravityAffected() {
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->getGravityAffected();
}

glm::dvec3 BoxCollider::getExtents() {
    return extents;
}

void BoxCollider::initInertiaTensor() {
    
    glm::dmat3x3 temp;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = 0;
        }
    }
}

void BoxCollider::translate(glm::dvec3 position) {
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(position + GetPosition());
}
void BoxCollider::SetCollisionCategory(unsigned short category)
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCollisionCategory(category);
}
void BoxCollider::SetCollisionMaskBits(unsigned short maskBits)
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCollisionMaskBits(maskBits);  
}
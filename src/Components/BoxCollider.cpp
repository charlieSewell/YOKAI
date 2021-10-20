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

CollisionBody* BoxCollider::getCollisionBody() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID);
}

void BoxCollider::setLV(glm::dvec3 lv) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setLinearVelocity(lv);
}

glm::dvec3 BoxCollider::getLV() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getLinearVelocity();
}

void BoxCollider::setS(bool s) {
    PhysicsSystem::getInstance().getPhysicsBody(colliderID)->setIsStaticObject(s);
}

bool BoxCollider::getS() {
    return PhysicsSystem::getInstance().getPhysicsBody(colliderID)->getIsStaticObject();
}

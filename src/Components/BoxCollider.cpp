#include "BoxCollider.hpp"

BoxCollider::BoxCollider(GameObject* parent) : Component(parent){}

void BoxCollider::Awake()
{
    //extents = glm::vec3(1,1,1);
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
	m_colliderID = PhysicsSystem::getInstance().addAABB(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),extents.x,extents.y,extents.z);
}
void BoxCollider::SetExtents(glm::vec3 extent)
{
   extents = extent;
}

void BoxCollider::SetOrientation(glm::quat orientation)
{
	PhysicsSystem::getInstance().getCollisionBody(m_colliderID)->SetOrientation(orientation);
}

void BoxCollider::SetExtents(float x,float y, float z)
{
   extents = glm::vec3(x,y,z);
}

void BoxCollider::SetPosition(glm::vec3 newPosition)
{
	PhysicsSystem::getInstance().getCollisionBody(m_colliderID)->SetPosition(newPosition);
}

void BoxCollider::Update(float deltaTime)
{
	//std::cout << " " << m_parent->GetComponent<Transform>()->getPosition().x << " " << m_parent->GetComponent<Transform>()->getPosition().y << " " << m_parent->GetComponent<Transform>()->getPosition().z << std::endl;
}

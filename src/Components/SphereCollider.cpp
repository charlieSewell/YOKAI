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
	PhysicsSystem::getInstance().getCollisionBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
}

void SphereCollider::SetPosition(glm::vec3 newPosition)
{
    PhysicsSystem::getInstance().getCollisionBody(m_colliderID)->SetPosition(newPosition);
}

unsigned int SphereCollider::GetColliderID()
{
	return m_colliderID;
}

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

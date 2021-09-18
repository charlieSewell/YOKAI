#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    colliderID = PhysicsSystem::getInstance().addSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),0.05);
	PhysicsSystem::getInstance().getRigidBody(colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
}

void SphereCollider::Update(float deltaTime)
{
	if(NewVelocity != m_lastVelocity)
	{
		PhysicsSystem::getInstance().getRigidBody(colliderID)->SetLinearVelocity(NewVelocity);
		m_lastVelocity = NewVelocity;
	}
    m_parent->GetComponent<Transform>()->setPosition(PhysicsSystem::getInstance().getRigidBody(colliderID)->GetPosition());
}

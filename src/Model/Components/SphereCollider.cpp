#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    colliderID = PhysicsSystem::getInstance().addSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),1);
}

void SphereCollider::Update(float deltaTime)
{
	if(NewPosition != m_lastPosition)
	{
		//PhysicsSystem::getInstance().getRigidBody(colliderID)->ApplyForceToCentre(NewPosition);
		//PhysicsSystem::getInstance().getRigidBody(colliderID)->SetPosition(NewPosition);
		PhysicsSystem::getInstance().getRigidBody(colliderID)->SetLinearVelocity(NewPosition);
		m_lastPosition = NewPosition;
	}
	//PhysicsSystem::getInstance().getRigidBody(colliderID)->SetLinearVelocity(NewPosition);
	PhysicsSystem::getInstance().getRigidBody(colliderID)->ApplyForceToCentre(NewPosition);
    m_parent->GetComponent<Transform>()->setPosition(PhysicsSystem::getInstance().getRigidBody(colliderID)->GetPosition());

   // std::cout <<" "<< m_parent->GetComponent<Transform>()->getPosition().x<< " " << m_parent->GetComponent<Transform>()->getPosition().y<<" " << m_parent->GetComponent<Transform>()->getPosition().z <<std::endl;
}

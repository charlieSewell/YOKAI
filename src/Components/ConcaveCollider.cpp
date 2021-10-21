#include "ConcaveCollider.hpp"

ConcaveCollider::ConcaveCollider(GameObject* parent) : Component(parent){}

void ConcaveCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    modelID = m_parent->GetComponent<DrawableEntity>()->GetModelID();
	m_colliderID = PhysicsSystem::getInstance().addConcaveShape(3,m_parent->GetComponent<Transform>().get(),m_parent->GetComponent<DrawableEntity>()->GetModelID());
}

void ConcaveCollider::Update(float deltaTime)
{

}

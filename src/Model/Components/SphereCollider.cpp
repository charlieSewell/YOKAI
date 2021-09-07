#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
    colliderID = PhysicsSystem::getInstance().addSphere(5,m_parent->GetComponent<Transform>().get(),3);
    PhysicsSystem::getInstance().getRigidBody(colliderID)->SetPosition(glm::vec3(140,40,140));
}

void SphereCollider::Update(float deltaTime)
{
    m_parent->GetComponent<Transform>()->setPosition(PhysicsSystem::getInstance().getRigidBody(colliderID)->GetPosition());
    std::cout <<" "<< m_parent->GetComponent<Transform>()->getPosition().x<< " " << m_parent->GetComponent<Transform>()->getPosition().y<<" " << m_parent->GetComponent<Transform>()->getPosition().z <<std::endl;
}

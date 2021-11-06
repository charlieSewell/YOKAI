#include "SphereCollider.hpp"

SphereCollider::SphereCollider(GameObject* parent) : Component(parent){}

void SphereCollider::Start()
{
	if (!m_hasStarted)
	{
		if(m_parent->GetComponent<Transform>() == nullptr)
		{
			m_parent->AddComponent<Transform>();
		}
		m_colliderID = PhysicsSystem::getInstance().AddSphere(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(), m_radius);
		PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->GetPosition());
		SetCentreOfMass(GetPosition());
		SetGravityAffected(false);

		m_hasStarted = true;
	}
}

void SphereCollider::SetOrientation(glm::quat orientation) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetOrientation(orientation);
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->UpdateBody();
}

void SphereCollider::SetPosition(glm::vec3 newPosition) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(newPosition);
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->UpdateBody();
}

glm::vec3 SphereCollider::GetPosition() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetPosition();
}

glm::quat SphereCollider::GetOrientation() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetOrientation();
}

int SphereCollider::GetColliderID() 
{
    return m_colliderID;
}

void SphereCollider::Update(float deltaTime)
{
   glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->GetRotation());
   SetPosition(m_parent->GetComponent<Transform>()->GetPosition());
   SetOrientation(temp);
   //PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->UpdateBody();
}
void SphereCollider::LateUpdate(float deltaTime)
{
    m_parent->GetComponent<Transform>()->SetPosition(GetPosition());
    m_parent->GetComponent<Transform>()->SetRotation(GetOrientation());
}

void SphereCollider::PhysicsUpdate(float deltaTime) 
{
    //glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->getRotation());
    //SetPosition(m_parent->GetComponent<Transform>()->getPosition());
    //SetOrientation(temp);
    // PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->UpdateBody();
}

void SphereCollider::SetMass(double m) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetMass(m);
}

double SphereCollider::GetMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetMass();
}

double SphereCollider::GetInverseMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseMass();
}

void SphereCollider::SetCentreOfMass(glm::vec3 com) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::vec3 SphereCollider::GetCentreOfMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void SphereCollider::SetInertiaTensor() 
{

    glm::dmat3x3 temp = YokaiPhysics::SphereInertiaTensor(m_radius, GetMass());

    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetInertiaTensor(temp);
}

glm::mat3x3 SphereCollider::GetInertiaTensor() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::mat3x3 SphereCollider::GetInverseInertiaTensor() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void SphereCollider::SetLinearVelocity(glm::vec3 lv) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::vec3 SphereCollider::GetLinearVelocity() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void SphereCollider::SetAngularVelocity(glm::vec3 av) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::dvec3 SphereCollider::GetAngularVelocity() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetAngularVelocity();
}

void SphereCollider::SetIsStaticObject(bool s) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetIsStaticObject(s);
}

bool SphereCollider::GetIsStaticObject() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetIsStaticObject();
}

void SphereCollider::SetGravityAffected(bool g) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetGravityAffected(g);
}

bool SphereCollider::GetGravityAffected() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetGravityAffected();
}

void SphereCollider::SetRadius(double radius) 
{
    m_radius = radius;
}

double SphereCollider::GetRadius() 
{
    return m_radius;
}

void SphereCollider::Translate(glm::vec3 position) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(position + GetPosition());
}

void SphereCollider::Rotate(glm::vec3 angVelocity, float deltaTime) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));
}

void SphereCollider::StaticSet() 
{
    SetCollisionCategory(Physics::CATEGORY1);
    SetCollisionMaskBits(Physics::CATEGORY2);
    SetLinearVelocity(glm::dvec3(0, 0, 0));
    SetAngularVelocity(glm::dvec3(0, 0, 0));
    SetMass(999999999999999.0);
    SetIsStaticObject(true);
    SetGravityAffected(false);
    SetInertiaTensor();
}

void SphereCollider::SetCollisionCategory(unsigned short category)
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCollisionCategory(category);
}
void SphereCollider::SetCollisionMaskBits(unsigned short maskBits)
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCollisionMaskBits(maskBits);  
}
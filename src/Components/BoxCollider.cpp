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
    SetCentreOfMass(GetPosition());
    SetGravityAffected(false);
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

glm::dvec3 BoxCollider::GetPosition() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetPosition();
}

glm::quat BoxCollider::GetOrientation() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetOrientation();
}

int BoxCollider::GetColliderID()
{
	return m_colliderID;
}

void BoxCollider::Update(float deltaTime)
{
    Translate(GetLinearVelocity() * static_cast<double>(deltaTime));
    Rotate(GetAngularVelocity(), deltaTime);
    //Translate(GetLinearVelocity() * static_cast<double>(deltaTime));
    SetCentreOfMass(GetPosition());

    m_parent->GetComponent<Transform>()->setPosition(GetPosition());
    m_parent->GetComponent<Transform>()->setRotation(GetOrientation());
}

void BoxCollider::SetMass(double m) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetMass(m);
}

double BoxCollider::GetMass() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetMass();
}

double BoxCollider::GetInverseMass() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetInverseMass();
}

void BoxCollider::SetCentreOfMass(glm::dvec3 com) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::dvec3 BoxCollider::GetCentreOfMass() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void BoxCollider::SetInertiaTensor() 
{
    
    glm::dmat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, GetMass());

    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetInertiaTensor(temp);
}

glm::dmat3x3 BoxCollider::GetInertiaTensor() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::dmat3x3 BoxCollider::GetInverseInertiaTensor() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void BoxCollider::SetLinearVelocity(glm::dvec3 lv) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::dvec3 BoxCollider::GetLinearVelocity() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void BoxCollider::SetAngularVelocity(glm::dvec3 av) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::dvec3 BoxCollider::GetAngularVelocity() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetAngularVelocity();
}

void BoxCollider::SetIsStaticObject(bool s) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetIsStaticObject(s);
}

bool BoxCollider::GetIsStaticObject() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetIsStaticObject();
}

void BoxCollider::SetGravityAffected(bool g) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetGravityAffected(g);
}

bool BoxCollider::GetGravityAffected() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetGravityAffected();
}

glm::dvec3 BoxCollider::GetExtents() 
{
    return extents;
}

void BoxCollider::Translate(glm::dvec3 velocity) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(velocity + GetPosition());
    
    //m_offset = glm::dvec3(0, 0.3, 0.01);
    //PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(velocity + glm::dvec3(m_parent->GetComponent<Transform>()->getPosition()) + m_offset);
    //m_parent->GetComponent<Transform>()->setPosition(GetPosition() - m_offset);
}

void BoxCollider::Rotate(glm::dvec3 angVelocity, float deltaTime) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));

    //PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));
    
    //PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(m_parent->GetComponent<Transform>()->getRotation() + (0.5f * m_parent->GetComponent<Transform>()->getRotation() * glm::quat(0.0, angVelocity) * deltaTime)));
    //m_parent->GetComponent<Transform>()->setRotation(GetOrientation());
}

void BoxCollider::StaticSet() 
{
    SetLinearVelocity(glm::dvec3(0, 0, 0));
	SetAngularVelocity(glm::dvec3(0, 0, 0));
	SetMass(10000.0);
	SetIsStaticObject(true);
    SetGravityAffected(false);
	SetInertiaTensor();
}

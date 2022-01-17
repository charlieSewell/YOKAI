#include "BoxCollider.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Physics/Physics.hpp"
BoxCollider::BoxCollider(GameObject* parent) : Component(parent){}

void BoxCollider::Start()
{
	if(!m_hasStarted)
	{
		//extents = glm::vec3(1,1,1);
		if(m_parent->GetComponent<Transform>() == nullptr)
		{
			m_parent->AddComponent<Transform>();
		}
		m_colliderID = PhysicsSystem::getInstance().AddAABB(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),extents.x,extents.y,extents.z);
		PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->GetPosition());
		SetCentreOfMass(GetPosition());
		SetGravityAffected(false);

		m_hasStarted = true;
	}
}
void BoxCollider::SetExtents(glm::vec3 extent)
{
   extents = extent;
}

void BoxCollider::SetOrientation(glm::quat orientation)
{
	PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetOrientation(orientation);
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->UpdateBody();
}

void BoxCollider::SetExtents(float x,float y, float z)
{
   extents = glm::dvec3(x,y,z);
}

void BoxCollider::SetPosition(glm::vec3 newPosition)
{
	PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(newPosition);
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->UpdateBody();
}

glm::vec3 BoxCollider::GetPosition() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetPosition();
}

glm::quat BoxCollider::GetOrientation() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetOrientation();
}

unsigned int BoxCollider::GetColliderID()
{
	return m_colliderID;
}
void BoxCollider::Update(float deltaTime)
{
    glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->GetRotation());
    SetPosition(m_parent->GetComponent<Transform>()->GetPosition());
    SetOrientation(temp);
    
}
void BoxCollider::LateUpdate(float deltaTime)
{
    m_parent->GetComponent<Transform>()->SetPosition(GetPosition());
    m_parent->GetComponent<Transform>()->SetRotation(GetOrientation());
}

void BoxCollider::SetMass(float m) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetMass(m);
}

float BoxCollider::GetMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetMass();
}

float BoxCollider::GetInverseMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseMass();
}

void BoxCollider::SetCentreOfMass(glm::vec3 com) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::vec3 BoxCollider::GetCentreOfMass() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void BoxCollider::SetInertiaTensor() 
{
    
    glm::mat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, GetMass());

    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetInertiaTensor(temp);
}

glm::mat3x3 BoxCollider::GetInertiaTensor() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::mat3x3 BoxCollider::GetInverseInertiaTensor() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void BoxCollider::SetLinearVelocity(glm::vec3 lv) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::vec3 BoxCollider::GetLinearVelocity() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void BoxCollider::SetAngularVelocity(glm::vec3 av) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::vec3 BoxCollider::GetAngularVelocity() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetAngularVelocity();
}

void BoxCollider::SetIsStaticObject(bool s) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetIsStaticObject(s);
}

bool BoxCollider::GetIsStaticObject() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetIsStaticObject();
}

void BoxCollider::SetGravityAffected(bool g) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetGravityAffected(g);
}

bool BoxCollider::GetGravityAffected() 
{
    return PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->GetGravityAffected();
}

glm::dvec3 BoxCollider::GetExtents() 
{
    return extents;
}

void BoxCollider::Translate(glm::vec3 velocity) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetPosition(velocity + GetPosition());
}

void BoxCollider::Rotate(glm::vec3 angVelocity, float deltaTime) 
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));
}

void BoxCollider::StaticSet() 
{
    SetCollisionCategory(Physics::CATEGORY1);
    SetCollisionMaskBits(Physics::CATEGORY2);
    SetLinearVelocity(glm::dvec3(0, 0, 0));
	SetAngularVelocity(glm::dvec3(0, 0, 0));
	SetMass(10.0);
	SetIsStaticObject(true);
    SetGravityAffected(false);
	SetInertiaTensor();
}
void BoxCollider::SetCollisionCategory(unsigned short category)
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCollisionCategory(category);
}
void BoxCollider::SetCollisionMaskBits(unsigned short maskBits)
{
    PhysicsSystem::getInstance().GetPhysicsBody(m_colliderID)->SetCollisionMaskBits(maskBits);  
}
void BoxCollider::RenderGUI()
{
    glm::vec3 tempLinear = GetLinearVelocity();
    glm::vec3 tempAngular = GetAngularVelocity();
    if(ImGui::TreeNode("Box Collider"))
	{
		ImGui::DragFloat3("Linear Velocity: ", &tempLinear[0], 0.1f);
		ImGui::DragFloat3("Angular Velocity: ", &tempAngular[0], 0.1f);
        ImGui::TreePop();
        ImGui::Separator();
	}
    SetLinearVelocity(tempLinear);
    SetAngularVelocity(tempAngular);

    SetPosition(m_parent->GetComponent<Transform>()->GetPosition());
    glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->GetRotation());
    SetOrientation(temp);
}

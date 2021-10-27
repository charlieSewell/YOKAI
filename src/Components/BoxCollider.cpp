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
		m_colliderID = PhysicsSystem::getInstance().addAABB(m_parent->GetObjectID(),m_parent->GetComponent<Transform>().get(),extents.x,extents.y,extents.z);
		PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(m_parent->GetComponent<Transform>()->getPosition());
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
	PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(orientation);
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->UpdateBody();
}

void BoxCollider::SetExtents(float x,float y, float z)
{
   extents = glm::dvec3(x,y,z);
}

void BoxCollider::SetPosition(glm::vec3 newPosition)
{
	PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(newPosition);
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->UpdateBody();
}

glm::vec3 BoxCollider::GetPosition() 
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
    glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->getRotation());
    SetPosition(m_parent->GetComponent<Transform>()->getPosition());
    SetOrientation(temp);
    
}
void BoxCollider::LateUpdate(float deltaTime)
{
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

void BoxCollider::SetCentreOfMass(glm::vec3 com) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCentreOfMass(com);
}

glm::vec3 BoxCollider::GetCentreOfMass() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetCentreOfMass();
}

void BoxCollider::SetInertiaTensor() 
{
    
    glm::mat3x3 temp = YokaiPhysics::RectangleInertiaTensor(extents, GetMass());

    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetInertiaTensor(temp);
}

glm::mat3x3 BoxCollider::GetInertiaTensor() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetInertiaTensor();
}

glm::mat3x3 BoxCollider::GetInverseInertiaTensor() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetInverseInertiaTensor();
}

void BoxCollider::SetLinearVelocity(glm::vec3 lv) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetLinearVelocity(lv);
}

glm::vec3 BoxCollider::GetLinearVelocity() 
{
    return PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->GetLinearVelocity();
}

void BoxCollider::SetAngularVelocity(glm::vec3 av) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetAngularVelocity(av);
}

glm::vec3 BoxCollider::GetAngularVelocity() 
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

void BoxCollider::Translate(glm::vec3 velocity) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetPosition(velocity + GetPosition());
}

void BoxCollider::Rotate(glm::vec3 angVelocity, float deltaTime) 
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetOrientation(glm::normalize(GetOrientation() + (0.5f * GetOrientation() * glm::quat(0.0, angVelocity) * deltaTime)));
}

void BoxCollider::StaticSet() 
{
    SetCollisionCategory(Physics::CATEGORY1);
    SetCollisionMaskBits(Physics::CATEGORY2);
    SetLinearVelocity(glm::dvec3(0, 0, 0));
	SetAngularVelocity(glm::dvec3(0, 0, 0));
	SetMass(5.0);
	SetIsStaticObject(true);
    SetGravityAffected(false);
	SetInertiaTensor();
}
void BoxCollider::SetCollisionCategory(unsigned short category)
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCollisionCategory(category);
}
void BoxCollider::SetCollisionMaskBits(unsigned short maskBits)
{
    PhysicsSystem::getInstance().getPhysicsBody(m_colliderID)->SetCollisionMaskBits(maskBits);  
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

    SetPosition(m_parent->GetComponent<Transform>()->getPosition());
    glm::quat temp = glm::inverse(m_parent->GetComponent<Transform>()->getRotation());
    SetOrientation(temp);
}

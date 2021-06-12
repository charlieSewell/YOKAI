//PhysicsComponent.cpp - manages physics

#include "PhysicsComponent.hpp"
PhysicsComponent::PhysicsComponent(Transform &transform)
	: m_transformPtr(&transform)
{

}

void PhysicsComponent::updatePhysics()
{
    auto& physManager = PhysicsSystem::getInstance();
    rp3d::Vector3 temp = physManager.getRigidBody(colliderID)->getRigidBody()->getTransform().getPosition();
    m_transformPtr->setPosition(ReactMath::rp3dVecToGlm(temp));

}

void PhysicsComponent::registerPhysicsToggle()
{
	auto togglePhysicsReleased = [&]()
	{	
		if(m_physicsTogglePressed)
        {
            m_physicsTogglePressed = false;
        }

	};
	EMS::getInstance().add(NoReturnEvent::togglePhysicsReleased, togglePhysicsReleased);

	auto togglePhysicsPressed = [&]()
	{
		if(!m_physicsTogglePressed)
		{
			m_physicsActive = !m_physicsActive;
			if(m_physicsActive){
			    getCollider()->SetBodyType(rp3d::BodyType::DYNAMIC);
			}
			else{
                getCollider()->SetBodyType(rp3d::BodyType::STATIC);
			}
			m_physicsTogglePressed = true;
		}
	};
	EMS::getInstance().add(NoReturnEvent::togglePhysicsPressed, togglePhysicsPressed);
}

//easy to implement if needed
/*void PhysicsComponent::registerBoundingSphere(glm::vec3 *position, double radius)
{
	m_colliderID = PhysicsSystem::getInstance().addBoundingSphere(position, radius);
}*/

void PhysicsComponent::registerAABB(unsigned int ID, float width, float height, float length)
{
	colliderID = PhysicsSystem::getInstance().addAABB(ID,m_transformPtr, width, height, length);
}
void PhysicsComponent::deleteCollider()
{
    if(colliderID != -1)
    {
        PhysicsSystem::getInstance().deleteRigidBody(colliderID);
    }
}
void PhysicsComponent::registerSphere(unsigned int ID, float radius)
{
    colliderID = PhysicsSystem::getInstance().addSphere(ID,m_transformPtr,radius);

}
RigidBody * PhysicsComponent::getCollider() const{
    return PhysicsSystem::getInstance().getRigidBody(colliderID);

}
void PhysicsComponent::registerPhysicsComponent()
{
    luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
            .beginClass<PhysicsComponent>("physicsComponent")
                    .addFunction("getCollider",&PhysicsComponent::getCollider)
                    .addFunction("getVelocity",&PhysicsComponent::getCurrentVelocity)
                    .addFunction("setMaxVelocity",&PhysicsComponent::setmaxVelocity)
                    .addFunction("getMaxVelocity",&PhysicsComponent::getmaxVelocity)
                    .endClass();
}
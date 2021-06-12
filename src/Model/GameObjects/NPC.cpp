#include "NPC.hpp"

NPC::NPC(const std::string& modelName)
	: GameObject(), m_behaviours(AutomatedBehaviours(m_transform)), m_physicsComponent(m_transform),
	hit(false), health(100)
{
    modelID = ModelManager::getInstance().GetModelID(modelName);
    m_transform.setPosition(glm::vec3(0,0,0));
    m_transform.setScale(glm::vec3(0,0,0));
    animator.addModel(ModelManager::getInstance().GetModel(modelID));

	animator.setAnimation("ZombieWalk");

	LuaManager::getInstance().runScript("content/Scripts/stateMachine.lua");
	luaUpdate = luabridge::getGlobal(LuaManager::getInstance().getState(), "update");

}
NPC::~NPC(){
    m_physicsComponent.deleteCollider();
}
void NPC::draw() 
{	
	ModelManager::getInstance().DrawModel(modelID, m_transform.getMatrix(),animator.finalTransforms);
}


void NPC::setCollider(float width, float height, float length)
{
    m_physicsComponent.registerAABB(ID,width, height, length);
    m_physicsComponent.getCollider()->SetBodyType(rp3d::BodyType::STATIC);
    m_physicsComponent.getCollider()->SetBounciness(0.0);

	m_behaviours.rayCaster.setOwnColliderID(m_physicsComponent.getCollider()->getColliderID());
	m_behaviours.rayCaster.setExcludedColliderID(EMS::getInstance().fire(ReturnIntEvent::getPlayerColliderID));
}

void NPC::update(float dt)
{
	m_transform.setPosition(glm::vec3(m_transform.getPosition().x, TerrainFactory::getInstance().heightAt(m_transform.getPosition().x, m_transform.getPosition().z), m_transform.getPosition().z));
    m_physicsComponent.getCollider()->SetPosition(glm::vec3(m_transform.getPosition().x,m_transform.getPosition().y +2,m_transform.getPosition().z));
    m_physicsComponent.getCollider()->SetOrientation(m_transform.getRotation());
	m_behaviours.updateFeelers();
	groupAlert();

	luaUpdate(this);
    animator.BoneTransform(dt);
}

void NPC::groupAlert() const
{
	if (m_behaviours.frontFeelerHit != -1)
	{
		if (GameObjectManager::getInstance().getNPC(m_behaviours.frontFeelerHit))
		{
			if (!GameObjectManager::getInstance().getNPC(m_behaviours.frontFeelerHit)->m_behaviours.active)
				GameObjectManager::getInstance().getNPC(m_behaviours.frontFeelerHit)->m_behaviours.active = true;
		}
	}

	if (m_behaviours.feelerRightHit != -1)
	{
		if (GameObjectManager::getInstance().getNPC(m_behaviours.feelerRightHit))
		{
			if (!GameObjectManager::getInstance().getNPC(m_behaviours.feelerRightHit)->m_behaviours.active)
				GameObjectManager::getInstance().getNPC(m_behaviours.feelerRightHit)->m_behaviours.active = true;
		}
	}

	if (m_behaviours.feelerLeftHit != -1)
	{
		if (GameObjectManager::getInstance().getNPC(m_behaviours.feelerLeftHit))
		{
			if (!GameObjectManager::getInstance().getNPC(m_behaviours.feelerLeftHit)->m_behaviours.active)
				GameObjectManager::getInstance().getNPC(m_behaviours.feelerLeftHit)->m_behaviours.active = true;
		}
	}
}

void NPC::registerClass()
{
	AutomatedBehaviours::registerClass();
	Animator::registerClass();

	luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
		.deriveClass<NPC, GameObject>("NPC")
		.addProperty("behaviours", &NPC::m_behaviours)
		.addProperty("animator", &NPC::animator)
		.addProperty("hit", &NPC::hit, true)
		.addProperty("health", &NPC::health, true)
		.endClass();
}


#include "Player.hpp"
#include "Controller/GameObjectManager.hpp"
Player::Player()
	: m_camera(Camera()), m_movement(PlayerControlledMotion(m_transform)), m_physics(m_transform)
{

	m_movement.movementSpeed = 2000.0f;

	m_movement.lookSensitivity = 0.05f;
	m_movement.jumpSpeed = 25.0f;
	//m_mass = 0.025f;
	registerPosition();
	registerColliderID();
	m_movement.registerAllMovement(m_camera.m_frontDirection, m_camera.m_upDirection);
	m_physics.registerPhysicsToggle();

    health = 100;
    shields = 100;
}

void Player::draw() 
{
    gun.draw();
}

void Player::update(float dt)
{

	if(m_physics.m_physicsActive)
	{
        if(onBox)
        {
            m_movement.canJump = true;
        }
        else{
            m_movement.canJump = false;
        }
        if (m_physics.getCollider()->GetLinearVelocity().y > m_movement.jumpSpeed) 
        {
            m_physics.getCollider()->SetLinearVelocity(
                glm::vec3(m_physics.getCollider()->GetLinearVelocity().x, m_movement.jumpSpeed,
                          m_physics.getCollider()->GetLinearVelocity().z));
        }   
        if(m_movement.canJump)
        {
            m_physics.getCollider()->SetLinearVelocity(glm::vec3(0.0));
            m_physics.getCollider()->SetAngularVelocity(glm::vec3(0.0));

            if (m_movement.updateVector != glm::vec3{})
            { 
                
                m_physics.getCollider()->ApplyForceToCentre(glm::normalize(glm::vec3(m_movement.updateVector.x,m_movement.updateVector.y,m_movement.updateVector.z)) * (m_movement.movementSpeed * m_movement.sprint) * dt);

            }
        }
    }
	else
	{
        if (m_movement.updateVector != glm::vec3{})
        {
            m_movement.canJump = true;
            m_physics.getCollider()->SetPosition(m_physics.getCollider()->GetPosition()+m_movement.updateVector);

        }
	}

    m_physics.updatePhysics();
    m_movement.updateVector = glm::vec3{};

	m_camera.m_position = glm::vec3(m_transform.getPosition().x, m_transform.getPosition().y + 3, m_transform.getPosition().z);		//TODO: make this better

	if (gun.getIsFiring() && gun.canFire)
		fireWeapon(200);

	if (gun.getIsMeleeing() && gun.canFire)
		fireWeapon(10);

	gun.getWeaponAnimation()->setCurrentFrame(dt);
	gun.update(m_camera.m_position, m_camera.m_frontDirection);
    LuaManager::getInstance().runScript("content/Scripts/playerLogic.lua");
    LuaManager::getInstance().runScript("content/Scripts/gunLogic.lua");
    onBox = false;

	if(hit)
		takeDamage(dt);
}

void Player::fireWeapon(float rayCastDistance)
{
	int targetID = rayCaster.CastRay(m_camera.m_position, m_camera.m_frontDirection, rayCastDistance);

	if (targetID != -1 && GameObjectManager::getInstance().getNPC(targetID))
	{
		//GameObjectManager::getInstance().getNPC(targetID)->hit = true;
		if (GameObjectManager::getInstance().getNPC(targetID)->health < 0)		//dead
		{
			GameObjectManager::getInstance().DeleteGameObject(targetID);
            LuaManager::getInstance().runScript("content/Scripts/enemyCount.lua");
			gun.setReserveAmmo(gun.getReserveAmmo() + 15);
			if(gun.getReserveAmmo() > 150)
				gun.setReserveAmmo(150);
		}
		else
			GameObjectManager::getInstance().getNPC(targetID)->hit = true;
	}
}

void Player::setCollider(float width, float length, float height)
{
    m_physics.registerSphere(ID,1);
    m_physics.getCollider()->SetMass(0.8);
    m_physics.getCollider()->SetIsAllowedToSleep(false);
    m_physics.getCollider()->SetFrictionCoefficient(0.2);
    m_physics.getCollider()->SetAngularDamping(0.2);
    m_physics.getCollider()->SetLinearDamping(0.2);
    m_physics.getCollider()->SetBounciness(0);
    rayCaster.setOwnColliderID( m_physics.getCollider()->getColliderID());
}

void Player::setHealth(int h) 
{
    health = h;
}

int Player::getHealth() const
{
    return health;
}

void Player::setShields(int s) 
{
    shields = s;
}

int Player::getShields() const
{
    return shields;
}

void Player::registerPosition()
{
	auto getPlayerPosition = [&]()
	{
		return m_transform.getPosition();
	};

	EMS::getInstance().add(ReturnVec3Event::getPlayerPosition, getPlayerPosition);
}

void Player::registerColliderID()
{
	auto getPlayerColliderID = [&]()
	{
		return m_physics.getCollider()->getColliderID();
	};

	EMS::getInstance().add(ReturnIntEvent::getPlayerColliderID, getPlayerColliderID);
}

void Player::takeDamage(float dt)
{
	if (takingDamage > dt * 60)
	{
		takingDamage = 0;
		if (shields > 0)
			shields -= 5;
        else 
		{
            health -= 5;
		}
		hit = false;
	}
	else
    {
        takingDamage += dt;
    }

}

void Player::registerClass()
{
	PlayerControlledMotion::registerClass();
	Weapon::registerClass();
	PhysicsComponent::registerPhysicsComponent();
	luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
		.deriveClass<Player, GameObject>("Player")
		.addProperty("movement", &Player::m_movement)
		.addProperty("health", &Player::health, true)
		.addProperty("shields", &Player::shields, true)
		.addProperty("gun", &Player::gun, true)
		.addProperty("physics",&Player::m_physics,true)
		.addProperty("onGround",&Player::onBox,true)
		.addProperty("hit", &Player::hit, true)
		.endClass();
}
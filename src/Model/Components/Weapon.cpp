#include "Model/Components/Weapon.hpp"

Weapon::Weapon() 
	: canFire(false), aimDownSights(false)
{
    maxAmmo = 30;
    maxReserveAmmo = 150;
    m_ammo = maxAmmo;
    reserveAmmo = maxReserveAmmo;
    isFiring = false;
    isReloading = false;

    weaponAnimation = new KeyframeAnimation();
    registerFire();
	registerMelee();
    registerReload();
	registerADS();
}

void Weapon::setCollider(float length, float height,float width)
{

}

KeyframeAnimation *Weapon::getWeaponAnimation()
{
    return weaponAnimation;
}

void Weapon::incrementAmmo() 
{
    if (reserveAmmo <= (maxReserveAmmo - maxAmmo)) 
    {
        reserveAmmo += maxAmmo;
    } 
    else 
    {
        reserveAmmo = maxReserveAmmo;
    }
}

void Weapon::decrementAmmo() 
{
    if (m_ammo > 0) 
    {
        m_ammo--;
    }
}

void Weapon::setAmmo(int a) 
{
    m_ammo = a;
}

int Weapon::getAmmo() const 
{
    return m_ammo;
}

void Weapon::setReserveAmmo(int r) 
{
    reserveAmmo = r;
}

int Weapon::getReserveAmmo() const 
{
    return reserveAmmo;
}

void Weapon::setMaxAmmo(int m) 
{
    maxAmmo = m;
}

int Weapon::getMaxAmmo() const 
{
    return maxAmmo;
}

void Weapon::setMaxReserveAmmo(int m) 
{
    maxReserveAmmo = m;
}

int Weapon::getMaxReserveAmmo() const 
{
    return maxReserveAmmo;
}

void Weapon::reload() 
{
    reserveAmmo += m_ammo;
    m_ammo = 0;
    reserveAmmo -= maxAmmo;

    if (reserveAmmo <= 0) 
    {
        m_ammo = maxAmmo + reserveAmmo;
        reserveAmmo = 0;
    } 
    else 
    {
        m_ammo = maxAmmo;
    }
}

void Weapon::draw() 
{
    weaponAnimation->draw(m_transform);
}

void Weapon::update(glm::vec3 position, glm::vec3 frontDirection)
{
	glm::mat4 matrix = glm::inverse(EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
	m_transform = Transform(matrix);
	m_transform.setPosition(position);

	if(aimDownSights)
	{
		m_transform.scale(0.022);
		m_transform.rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
		m_transform.translate(0, -22.125, 0);
		m_transform.translatePostMultiply(static_cast<float>(glm::normalize(frontDirection).x * 0.5), static_cast<float>(glm::normalize(frontDirection).y * 0.5), static_cast<float>(glm::normalize(frontDirection).z * 0.5));
		/*
		m_transform.scale(0.022);
		m_transform.rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
		m_transform.translatePostMultiply(static_cast<float>(glm::normalize(frontDirection).x), static_cast<float>(glm::normalize(frontDirection).y + 2.51), static_cast<float>(glm::normalize(frontDirection).z));
		m_transform.translatePostMultiply(frontDirection * -0.65f);
		glm::vec3 rightVector = glm::normalize((glm::cross(frontDirection, glm::vec3(0, 1, 0))));
		m_transform.translatePostMultiply(glm::normalize(rightVector) * -0.003f);
		*/
	}
	else
	{
		//m_transform.translate(0, -22, 0);
		//m_transform.translatePostMultiply(static_cast<float>(glm::normalize(frontDirection).x * 0.5), static_cast<float>(glm::normalize(frontDirection).y * 0.5), static_cast<float>(glm::normalize(frontDirection).z * 0.5));

		m_transform.scale(0.02);
		m_transform.rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
		
		m_transform.translatePostMultiply(static_cast<float>(glm::normalize(frontDirection).x * 0.7), static_cast<float>(glm::normalize(frontDirection).y - 0.55), static_cast<float>(glm::normalize(frontDirection).z * 0.75));
		glm::vec3 rightVector = glm::normalize((glm::cross(frontDirection, glm::vec3(0, 1, 0))));
		m_transform.translatePostMultiply(glm::normalize(rightVector) * 0.45f);
	}
}

void Weapon::registerFire() 
{
    auto fire = [&]() 
    { 
        isFiring = true;
    };

    EMS::getInstance().add(NoReturnEvent::mouseClicked, fire);

    auto noFire = [&]() 
    { 
        isFiring = false; 
    };

    EMS::getInstance().add(NoReturnEvent::mouseReleased, noFire);
}

bool Weapon::getIsFiring() const
{
    return isFiring;
}

void Weapon::registerMelee()
{
	auto melee = [&]()
	{
		isMeleeing = true;
	};

	EMS::getInstance().add(NoReturnEvent::meleePressed, melee);

	auto noMelee = [&]()
	{
		isMeleeing = false;
	};

	EMS::getInstance().add(NoReturnEvent::meleeReleased, noMelee);
}

bool Weapon::getIsMeleeing() const
{
	return isMeleeing;
}

void Weapon::registerReload() 
{
    auto reload = [&]() 
    { 
        isReloading = true; 
    };

    EMS::getInstance().add(NoReturnEvent::reloadPressed, reload);

    auto noReload = [&]() 
    { 
        isReloading = false; 
    };

    EMS::getInstance().add(NoReturnEvent::reloadReleased, noReload);
}

bool Weapon::getIsReloading() const
{
	return isReloading;
}

void Weapon::registerADS()
{
	auto ads = [&]()
	{
		aimDownSights = true;
	};

	EMS::getInstance().add(NoReturnEvent::mouse2Clicked, ads);

	auto hipFire = [&]()
	{
		aimDownSights = false;
	};

	EMS::getInstance().add(NoReturnEvent::mouse2Released, hipFire);
}

void Weapon::registerClass()
{
	KeyframeAnimation::registerClass();
	luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
		.beginClass<Weapon>("Weapon")
		.addProperty("gunAnimation", &Weapon::weaponAnimation, true)
		.addProperty("ammo", &Weapon::getAmmo, &Weapon::setAmmo)
		.addProperty("reserveAmmo", &Weapon::getReserveAmmo, &Weapon::setReserveAmmo)
		.addProperty("maxAmmo", &Weapon::getMaxAmmo, &Weapon::setMaxAmmo)
		.addProperty("maxReserveAmmo", &Weapon::getMaxReserveAmmo, &Weapon::setMaxReserveAmmo)
		.addProperty("canFire", &Weapon::canFire, true)
		.addProperty("ads", &Weapon::aimDownSights, true)
		.addFunction("reload", &Weapon::reload)
		.addFunction("getIsFiring", &Weapon::getIsFiring)
		.addFunction("getIsMeleeing", &Weapon::getIsMeleeing)
		.addFunction("getIsReloading", &Weapon::getIsReloading)
		.addFunction("incrementAmmo", &Weapon::incrementAmmo)
		.addFunction("decrementAmmo", &Weapon::decrementAmmo)
		.endClass();
}


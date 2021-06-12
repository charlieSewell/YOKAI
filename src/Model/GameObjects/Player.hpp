//Player.hpp

#pragma once
#include "Model/Components/Camera.hpp"
#include "Model/Components/PhysicsComponent.hpp"
#include "Model/Components/PlayerControlledMotion.hpp"
#include "Model/GameObjects/GameObject.hpp"
#include "Model/Components/Weapon.hpp"
#include "Controller/LuaManager.hpp"
#include "Model/Components/RayCaster.hpp"
#include "Model/SplashScreen.hpp"
/**
 * @class Player
 * @brief Child of GameObject for the player within the game. Inherits physics component, camera and player controlled motion
 */
class Player : public GameObject
{

public:
    /*!
     * @brief Constructor
     */
	Player();

	/*!
     * @brief Deconstructor
     */
	~Player() = default;

    /*!
     * @brief Draw call for the player model
     */
	void draw();

    /*!
     * @brief Update call for the player
     */
	void update(float dt) override;
	/**
	 * @brief Sets the collider for the player
	 * @param width
	 * @param length
	 * @param height
	 */

	/**
	* @brief fires weapon
	*/
	void fireWeapon(float rayCastDistance);

    void setCollider(float width, float length, float height) override;
    /**
     * @brief Sets the health for the player
     * @param h
     */
    void setHealth(int h);
    /**
     * @brief Gets Current Player Health
     * @return
     */
    int getHealth() const;
    /**
     * @brief Sets the players shields value
     * @param s
     */
    void setShields(int s);
    /**
     * @brief Gets the players shield ammount
     * @return
     */
    int getShields() const;
    /**
     * @brief Registers Class in Lua
     */
	static void registerClass();
	///Movement Component
    PlayerControlledMotion m_movement;
    ///Physics Component
    PhysicsComponent m_physics;
    ///is on the ground
    bool onBox = false;
	//player has been hit
	bool hit = false;
	//player is taking damage
	float takingDamage = false;
	//resolves the player damage
	void takeDamage(float dt);
  private:
    ///Camera component
	Camera m_camera;
	///Weapon Component
    Weapon gun;
    ///Ray caster Component
    RayCaster rayCaster;
    ///registers player position with EMS
	void registerPosition();
    ///registers player colliderID with EMS
	void registerColliderID();
    ///health of player
    int health;
    ///shields of player
    int shields;
};

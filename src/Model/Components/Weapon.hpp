#pragma once

#include <iostream>
#include "Controller/KeyframeAnimation.hpp"
#include "Model/GameObjects/GameObject.hpp"
#include "Controller/LuaManager.hpp"
/**
 * @class Weapon
 * @brief class that defines a weapon
 */
class Weapon : public GameObject
{
  public:
    /**
     * @brief Default constructor
     */
    Weapon();
    /**
     * @brief Reload the weapon
     */
    void reload();
/**
 * @brief Sets the ammo
 * @param a
 */
    void setAmmo(int a);
    /**
     * @brief Gets the ammo
     * @return
     */
    int getAmmo() const;

    /**
     * @brief sets reserve ammo
     * @param r
     */
    void setReserveAmmo(int r);
    /**
     * @brief gets reserve ammo
     * @return
     */
    int getReserveAmmo() const;
    /**
     * @brief Increments ammo by 1
     */
    void incrementAmmo();
    /**
     * @brief Decrements ammo by 1
     */
    void decrementAmmo();
    /**
     * @brief Sets max ammo count
     * @param a
     */
    void setMaxAmmo(int a);
    /**
     * @brief Gets max ammo count
     * @return int
     */
    int getMaxAmmo() const;

    /**
     * @brief Sets max reserve ammo
     * @param r
     */
    void setMaxReserveAmmo(int r);
    /**
     * @brief Gets max reserve ammo
     * @return int
     */
    int getMaxReserveAmmo() const;
    /// Model and animation of the weapon
    KeyframeAnimation *getWeaponAnimation();
    /**
     * @brief Updates the weapon
     * @param playerTransform
     * @param frontDirection
     */
    void update(glm::vec3 position, glm::vec3 frontDirection);
    /**
     * @brief Draws the weapon
     */
    void draw() override;
    /**
     * @brief Sets the collider of the weapon
     * @param width
     * @param length
     * @param height
     */
    void setCollider(float width, float length, float height) override;
    /**
     * @brief Register the class with lua
     */
    static void registerClass();
    /**
     * @brief registers the fire event
     */
    void registerFire();
    /**
     * @brief Get is Firing
     * @return bool
     */
    bool getIsFiring() const;
	/**
	* @brief Get is Meleeing
	* @return bool
	*/
	bool getIsMeleeing() const;
    /**
     * @brief registers is Firing
     */
    void registerReload();
	/**
	* @brief registers is meleeing
	*/
    void registerMelee();
	/**
	* @brief registers aimDownSights
	*/
	void registerADS();
    /**
     * @brief Gets whether weapon is reloading
     * @return
     */
    bool getIsReloading() const;

	bool canFire;

  private:
    ///Weapon to animate
    KeyframeAnimation *weaponAnimation;
    ///max ammo
    int maxAmmo;
    ///current ammo
    int m_ammo;
    ///max reserve ammo
    int maxReserveAmmo;
    ///reserve ammo
    int reserveAmmo;
    ///is weapon firing
    bool isFiring;
	///is weapon meleeing
	bool isMeleeing;
    ///is weapon reloading
    bool isReloading;
	//aim down sights
	bool aimDownSights;
};
#pragma once
#include <glm/glm.hpp>
#include "Controller/ModelManager.hpp"
#include "GameObject.hpp"
#include "Model/Components/PhysicsComponent.hpp"
#include "Model/Components/AutomatedBehaviours.hpp"
#include <Controller/Animator.hpp>
#include "Controller/LuaManager.hpp"
/**
 * @class NPC
 * @brief Child of GameObject for all NPC's within the game. Inherits physics component.
 */
class NPC : public GameObject
{
  public:
    /*!
     * @brief Constructor
     * @param string - modelName
     */
    NPC(const std::string& modelName);
    ~NPC();

    /*!
     * @brief Draw call for the NPC model
     */
    void draw();
    /**
     * @brief Updates the game object
     * @param dt
     */
    void update(float dt) override;
    /**
     * @brief Sets the collider of the object
     * @param width
     * @param height
     * @param length
     */
	void setCollider(float width, float height, float length) override;

	bool hit;
	int health;

    

/**
 * @brief Registers class in lua
 */
	static void registerClass();

	///Behaviours component
	AutomatedBehaviours m_behaviours;
private:
	///Physics component
	PhysicsComponent m_physicsComponent;
	///Animator component
	Animator animator;
    /**
     * @brief Group allert for AI
     */
	void groupAlert() const;	//bad
    /// Stores associated model id of the NPC
    int modelID;
    ///Lua stateMachine
	luabridge::LuaRef luaUpdate = LuaManager::getInstance().getState();
};

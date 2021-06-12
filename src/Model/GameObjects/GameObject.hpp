//GameObject.hpp

#pragma once

#include "View/Renderer/Shader.hpp"
#include "Controller/LuaManager.hpp"
#include "Model/Components/Transform.hpp"

/**
 * @class GameObjectType
 * @brief Stores enum values for the types of GameObjects
 */
enum class GameObjectType
{
	player, staticObject, npc
};

/**
 * @class GameObject
 * @brief Responsible for functions of every object created within the game
 */
class GameObject
{
public:
	GameObject();
    virtual ~GameObject() = 0;
    /*!
     * @brief Registers the class for Lua
     */
    static void registerClass();

    /*!
     * @brief Virtual getter for the transform of the GameObject
     * @return m_transform
     */
    virtual Transform getTransform();

    virtual void setTransform(Transform transform);

	/*!
	* @brief Virtual getter for the position of the GameObject
	* @return m_position
	*/
	virtual glm::vec3 getLuaPosition();

    virtual void setCollider(float x,float y,float z) = 0;

    /*!
     * @brief Virtual setter for the GameObject position within Lua
     * @param float - x
     * @param float - y
     * @param float - z
     */
    virtual void setLuaPosition(float x,float y,float z);

    /*!
     * @brief Virtual setter for the GameObject scale within Lua
     * @param float - x
     * @param float - y
     * @param float - z
     */
    virtual void setLuaScale(float x,float y,float z);

    /*!
     * @brief Virtual update call for the GameObject
     */
	virtual void update(float dt);

    /*!
     * @brief Pure virtual draw call for the GameObject
     */
    virtual void draw() = 0;

    void setID(unsigned int ID){this->ID = ID;}
    /// Transform of the GameObject
    Transform m_transform;
protected:
	/// Type of GameObject
	GameObjectType m_EntityType;
    ///ID of Game Object
	unsigned int ID;


};

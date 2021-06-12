#pragma once
#include <map>
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/LuaTypes.hpp"
#include "Model/GameObjects/GameObject.hpp"

class NPC;
class Player;

/**
 * @class GameObjectManager
 * @brief Responsible for the management of all game objects created
 */
class GameObjectManager
{
  public:
    /*!
     * @brief Singleton Pattern for a single instance of the class
     * @return instance
     */
    static GameObjectManager &getInstance();

    /*!
     * @brief Initialises the manager
     */
    void init();

    /*!
     * @brief Creates a GameObject and stores it within a map of GameObjects
     * @param GameObjectType - type
     * @param string - model
     * @return objectCount-1
     */
    int CreateObject(GameObjectType type, std::string model);

    /*!
     * @brief Adds a GameObject to the map of GameObjects
     * @param GameObject smart pointer - &gameObject
     * @return objectCount-1
     */
    int add(std::shared_ptr<GameObject> &gameObject);

    /*!
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject
     */
    std::shared_ptr<GameObject> getObject(int id);

    /*!
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject pointer
     */
    GameObject* luaGet(int id);

    /*!
     * @brief Getter for Gameobject with player id
     * @return Player*
     */

    Player* getPlayer();

    /*!
     * @brief Calls the update function for all GameObjects
     */
    void update(float dt);

    /*!
     * @brief Calls the draw function for all GameObjects
     */
    void draw();
    /*!
     * @brief Deletes a game object by ID
     * @param unsigned int - id
     */
    void DeleteGameObject(unsigned int id);

	/**
	 * @brief Gets NPC by ID
	 * @param id
	 * @return NPC*
	 */
    NPC* getNPC(int id);

	//elapsed time
	float elapsedTime;

	/**
	 * @brief Utility function for lua
	 * @return distance
	 */
	float luaDistance(glm::vec3, glm::vec3);
    /**
     * @brief DeInitialises all game objects
     */
    void DeInit();

  private:
    /*!
     * @brief Constructor
     */
    GameObjectManager();
    ~GameObjectManager();
    /// Map of GameObjects, with the key of the GameObject id, and value of the GameObject smart pointer
    std::map<int, std::shared_ptr<GameObject>> gameObjects;

    /// Stores the number of GameObjects within the map
    int objectCount = 0;

    /// Stores the id of the player GameObject
    int playerID = 0;
};

#pragma once
#include <map>

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
    //int CreateObject(GameObjectType type, std::string model);

    /*!
     * @brief Adds a GameObject to the map of GameObjects
     * @param GameObject smart pointer - &gameObject
     * @return objectCount-1
     */
    //int add(std::shared_ptr<GameObject> &gameObject);

    /*!
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject
     */
    //std::shared_ptr<GameObject> getObject(int id);

    /*!
     * @brief Getter for Gameobject with player id
     * @return Player*
     */

    /*!
     * @brief Calls the update function for all GameObjects
     */
    //void update(float dt);

    /*!
     * @brief Calls the draw function for all GameObjects
     */
    //void draw();
    /*!
     * @brief Deletes a game object by ID
     * @param unsigned int - id
     */

    //void DeleteGameObject(unsigned int id);

	//elapsed time
	float elapsedTime;


    /**
     * @brief DeInitialises all game objects
     */
    //void DeInit();

  private:
    /*!
     * @brief Constructor
     */
    GameObjectManager();
    ~GameObjectManager();
    /// Map of GameObjects, with the key of the GameObject id, and value of the GameObject smart pointer
    //std::map<int, std::shared_ptr<GameObject>> gameObjects;

    /// Stores the number of GameObjects within the map
    int objectCount = 0;
};

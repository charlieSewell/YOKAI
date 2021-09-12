#pragma once
#include <map>
#include "Model/GameObject.hpp"
#include "Controller/Export.hpp"
/**
 * @class GameObjectManager
 * @brief Responsible for the management of all game objects created
 */
class YOKAI_API GameObjectManager
{
  public:
    GameObjectManager();
    ~GameObjectManager();
    /*!
     * @brief Creates a GameObject and stores it within a map of GameObjects
     * @return objectCount-1
     */
    unsigned int CreateObject();
    /*!
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject
     */
    std::shared_ptr<GameObject> GetObject(unsigned int id);

    /*!
     * @brief Calls the update function for all GameObjects
     */
    void Update(float dt);

    /*!
     * @brief Calls the draw function for all GameObjects
     */
    void Draw();

    void DeleteGameObject(unsigned int id);
  private:
    /// Map of GameObjects, with the key of the GameObject id, and value of the GameObject smart pointer
    std::map<unsigned int,std::shared_ptr<GameObject>> gameObjects;

    /// Stores the number of GameObjects within the map
    unsigned int objectCount;
};

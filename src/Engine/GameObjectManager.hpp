#pragma once
#include <map>
#include "GameObject.hpp"
#include "imgui/imgui.h"
/**
 * @class GameObjectManager
 * @brief Responsible for the management of all game objects created
 */
class GameObjectManager
{
  public:
    /**
     * @brief Constructs the Game Object Manager object
     */
    GameObjectManager();
    /**
     * @brief Destroy the Game Object Manager object
     */
    ~GameObjectManager();
    /**
     * @brief Creates a GameObject and stores it within a map of GameObjects
     * @return unsigned int 
     */
    unsigned int CreateObject();
    /**
     * @brief Create a GameObject and stores it within a map of GameObjects
     * @param objectName 
     * @return unsigned int 
     */
    unsigned int CreateObject(std::string objectName);
    /**
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject
     */
    std::shared_ptr<GameObject> GetObject(unsigned int id);
    /**
     * @brief Calls the update function for all GameObjects
     */
    void Update(float dt);
    /**
     * @brief Update After Physics Simulation
     * @param dt 
     */
    void LateUpdate(float dt);
    /**
     * @brief Serialises all GameObjects
     * @param j 
     */
    void Serialize(nlohmann::json &j);
    /**
     * @brief Calls the draw function for all GameObjects
     */
    void Draw();
    /**
     * @brief Deletes Game Objects given an ID
     * @param id 
     */
    void DeleteGameObject(unsigned int id);
    /**
     * @brief Renders GUI
     */
    void RenderGUI();
    /**
     * @brief Clears the Game Object Manager
     */
    void Clear();
  private:
    /// Map of GameObjects, with the key of the GameObject id, and value of the GameObject smart pointer
    std::map<unsigned int,std::shared_ptr<GameObject>> m_gameObjects;
    /// Stores the number of GameObjects within the map
    unsigned int m_objectCount;
};

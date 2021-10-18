#pragma once

#include <map>
#include "Model/SplashScreen.hpp"

/**
 * @class GameObjectManager
 * @brief Responsible for the management of all game objects created
 */
class UIManager 
{
  public:
    /*!
     * @brief Singleton Pattern for a single instance of the class
     * @return instance
     */
    static UIManager &getInstance();

    /*!
     * @brief Initialises the manager
     */
    void init();

    std::shared_ptr<SplashScreen> create(const std::string& texturePath);
    /*!
     * @brief Adds a GameObject to the map of GameObjects
     * @param GameObject smart pointer - &gameObject
     * @return objectCount-1
     */
    std::string add(std::string name, const std::string& texturePath);

    /*!
     * @brief Getter for a GameObject with the specified id
     * @param int - id
     * @return GameObject
     */
    std::shared_ptr<SplashScreen> getObject(const std::string& name);

    /*!
     * @brief Calls the update function for all GameObjects
     */
    void update(float dt);

    /*!
     * @brief Calls the draw function for all GameObjects
     */
    void draw();

    /**
     * @brief Deinitialises The UI Manager
     */
    void DeInit();

  private:
    /*!
     * @brief Constructor
     */
    UIManager() = default;

    /// Map of GameObjects, with the key of the GameObject id, and value of the GameObject smart pointer
    std::map<std::string, std::shared_ptr<SplashScreen>> uiObjects;
    ///Pointer to shader
    Shader *splashShader;
};

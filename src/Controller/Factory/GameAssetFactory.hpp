#pragma once
#include <iostream>
#include "Controller/ModelManager.hpp"
#include "Model/GameObjects/GameObject.hpp"
#include "Model/GameObjects/NPC.hpp"
#include "Model/GameObjects/StaticObject.hpp"
#include "Model//GameObjects/Player.hpp"

/**
 * @class GameAssetFactory
 * @brief Responsible for the creation of game objects
 */
class GameAssetFactory
{
  public:
     /*!
     * @brief Creates a GameObject with the specified type of enum, and path to the model of the object.
     * @param GameObjectType - type enum.
     * @param String - modelName
     * @return GameObject smart pointer
     */
	static std::shared_ptr<GameObject> Create(GameObjectType type, std::string modelName);
    
    /*!
     * @brief Creates a GameObject with the specified type of enum
     * @param GameObjectType - type enum.
     * @return GameObject smart pointer
     */
	static std::shared_ptr<GameObject> Create(GameObjectType type);

	//std::shared_ptr<GameObject> GameAssetFactory::Create(GameObjectType type, std::string modelName, glm::vec3 position);
};

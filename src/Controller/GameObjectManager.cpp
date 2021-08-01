#include "GameObjectManager.hpp"

#include <utility>
#include <spdlog/spdlog.h>

GameObjectManager::GameObjectManager()
	: elapsedTime(0)
{

}

GameObjectManager& GameObjectManager::getInstance() 
{
    static GameObjectManager instance;
    return instance;
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::init()
{
    SPDLOG_INFO("Game Object Manager Initialised. FIX ME");
}

/*int GameObjectManager::CreateObject(GameObjectType type,std::string model)
{

}*/

/*int GameObjectManager::add(std::shared_ptr<GameObject>& gameObject)
{

}*/

/*void GameObjectManager::DeInit()
{

}*/

/*void GameObjectManager::DeleteGameObject(unsigned int id)
{

}*/

/*void GameObjectManager::update(float dt)
{

}*/

/*void GameObjectManager::draw()
{

}*/

/*std::shared_ptr<GameObject> GameObjectManager::getObject(int id) 
{

}*/
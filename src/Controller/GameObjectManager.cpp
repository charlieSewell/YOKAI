#include "GameObjectManager.hpp"

#include <utility>
#include <spdlog/spdlog.h>

GameObjectManager::GameObjectManager() : objectCount(0) {}

GameObjectManager::~GameObjectManager()
{
    gameObjects.clear();
}


unsigned int GameObjectManager::CreateObject()
{
    gameObjects.emplace(objectCount,std::make_shared<GameObject>(objectCount));
    return objectCount++;
}


void GameObjectManager::DeleteGameObject(unsigned int id)
{
    gameObjects.erase(id);
}

void GameObjectManager::Update(float dt)
{
    for(auto& object : gameObjects)
    {
        object.second->Update(dt);
    }
}

void GameObjectManager::Draw()
{
    for(auto& object : gameObjects)
    {
        object.second->Draw();
    }
}

std::shared_ptr<GameObject> GameObjectManager::GetObject(unsigned int id) 
{
    if(gameObjects.at(id)->GetObjectID() == id)
    {
        return gameObjects[id];
    }
    return nullptr; 
}
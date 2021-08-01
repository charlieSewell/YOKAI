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
    GameObject::registerClass();
	NPC::registerClass();
	Player::registerClass();
    luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
        .beginClass<GameObjectManager>("ObjectManager")
            .addStaticFunction("getInstance",&GameObjectManager::getInstance)
            .addFunction("Create",&GameObjectManager::CreateObject)
            .addFunction("GetObject",&GameObjectManager::luaGet)
            .addFunction("GetPlayer", &GameObjectManager::getPlayer)
            .addFunction("GetNPC", &GameObjectManager::getNPC)
            .addFunction("Update",&GameObjectManager::update)
			.addFunction("distance", &GameObjectManager::luaDistance)
			.addProperty("elapsedTime", &GameObjectManager::elapsedTime)
        .endClass();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getState())
        .beginNamespace("Types")
            .addFunction("npc",LuaTypes::getNPCType)
            .addFunction("player",LuaTypes::getPlayerType)
            .addFunction("static",LuaTypes::getStaticType)
        .endNamespace();

    LuaManager::getInstance().runScript("content/Scripts/createObjects.lua");
    SPDLOG_INFO("Game Object Manager Initialised");
}

int GameObjectManager::CreateObject(GameObjectType type,std::string model)
{
    if(type == GameObjectType::player){
        gameObjects[objectCount] = GameAssetFactory::Create(type);
        gameObjects[objectCount]->setID(objectCount);
        playerID = objectCount;
    }
    else
    {
        gameObjects[objectCount] = GameAssetFactory::Create(type,std::move(model));
        gameObjects[objectCount]->setID(objectCount);
    }

    objectCount++;

    return objectCount - 1;
}

int GameObjectManager::add(std::shared_ptr<GameObject>& gameObject)
{
    gameObject->setID(objectCount);
    gameObjects[objectCount] = gameObject;
    objectCount++;
    return objectCount - 1;
}
void GameObjectManager::DeInit(){
    gameObjects.clear();
}
void GameObjectManager::DeleteGameObject(unsigned int id)
{
    gameObjects.erase(id);
}

void GameObjectManager::update(float dt)
{
    for(auto& gameObject :gameObjects)
    {
        gameObject.second->update(dt);
    }

	elapsedTime += dt;
}
void GameObjectManager::draw()
{
    for(auto& gameObject :gameObjects)
    {
		if(gameObject.second != gameObjects[playerID])
			gameObject.second->draw();
    }
	getPlayer()->draw();
}

Player* GameObjectManager::getPlayer()
{
	return(dynamic_cast<Player*>(gameObjects[playerID].get()));
}

std::shared_ptr<GameObject> GameObjectManager::getObject(int id) 
{

    if(gameObjects[id] != nullptr)
    {
        return gameObjects[id];
    }
    return nullptr;
}

GameObject* GameObjectManager::luaGet(int id)
{

    if(gameObjects[id] != nullptr)
    {
        return gameObjects[id].get();
    }
    return nullptr;
}

NPC* GameObjectManager::getNPC(int id)
{ 
	return(dynamic_cast<NPC*>(gameObjects[id].get()));
}


float GameObjectManager::luaDistance(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::distance(vec1, vec2);
}
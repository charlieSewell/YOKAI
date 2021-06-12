#include "GameAssetFactory.hpp"

 std::shared_ptr<GameObject> GameAssetFactory::Create(GameObjectType type, std::string modelName) 
 {
    if (type == GameObjectType::staticObject) 
    {
        return std::shared_ptr<GameObject>(new StaticObject(modelName));
    } 
    else if (type == GameObjectType::npc) 
    {
        return std::shared_ptr<GameObject>(new NPC(modelName));
    }
    return nullptr;
 }

 std::shared_ptr<GameObject> GameAssetFactory::Create(GameObjectType type)
 {
	 if (type == GameObjectType::player)
	 {
		 return std::shared_ptr<GameObject>(new Player);
	 }
     return nullptr;
 }

/*std::shared_ptr<GameObject> GameAssetFactory::Create(GameObjectType type, std::string modelName, glm::vec3 position)
{
	 if (type == GameObjectType::staticObject)
	 {
		 return std::shared_ptr<GameObject>(new StaticObject(modelName, position);
	 }
	 else if (type == GameObjectType::npc)
	 {
		 return std::shared_ptr<GameObject>(new NPC(modelName, position));
	 }
 }*/

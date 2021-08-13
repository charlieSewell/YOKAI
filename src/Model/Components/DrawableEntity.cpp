#include "DrawableEntity.hpp"
#include "Controller/ModelManager.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/GameObject.hpp"

DrawableEntity::DrawableEntity(GameObject* parent) : Component(parent){}

void DrawableEntity::Start()
{
    if(parent->GetComponent<Transform>() == nullptr)
    {
        parent->AddComponent<Transform>();
    }
}
void DrawableEntity::Update(float deltaTime)
{

}
void DrawableEntity::Draw()
{
    ModelManager::getInstance().DrawModel(modelID,parent->GetComponent<Transform>()->getMatrix());
}
void DrawableEntity::LoadModel(std::string filename)
{
    modelID = ModelManager::getInstance().GetModelID(filename);
}
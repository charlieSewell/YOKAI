#include "DrawableEntity.hpp"

DrawableEntity::DrawableEntity(GameObject* parent) : Component(parent){}

void DrawableEntity::Start()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_parent->AddComponent<Transform>();
    }
}

void DrawableEntity::Update(float deltaTime)
{

}

void DrawableEntity::Draw()
{
    Yokai::getInstance().getModelManager()->DrawModel(modelID,m_parent->GetComponent<Transform>()->getMatrix());
}

void DrawableEntity::LoadModel(std::string filename)
{
    modelID = Yokai::getInstance().getModelManager()->GetModelID(filename);
}
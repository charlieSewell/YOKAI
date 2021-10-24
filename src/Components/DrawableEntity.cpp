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
    if(m_animator != nullptr)
    {
        m_animator->BoneTransform(deltaTime);
    }
}

void DrawableEntity::Draw()
{
    if(m_animator == nullptr)
    {
        Yokai::getInstance().getModelManager()->DrawModel(m_modelID,m_parent->GetComponent<Transform>()->getMatrix());
    }
    else
    {
        Yokai::getInstance().getModelManager()->DrawModel(m_modelID,m_parent->GetComponent<Transform>()->getMatrix(),m_animator->finalTransforms);
    }
  
}

void DrawableEntity::LoadModel(std::string filename)
{
    m_modelID = Yokai::getInstance().getModelManager()->GetModelID(filename);
    Model* model = Yokai::getInstance().getModelManager()->GetModel(m_modelID);
    if(model->isAnimated())
    {
        m_animator = new Animator(model);
    }
    else 
    {
        delete m_animator;
        m_animator = nullptr;
    }
}
void DrawableEntity::SetAnimation(std::string animation)
{
    m_animator->setAnimation(animation);
}
void DrawableEntity::RenderGUI()
{

}
#include "DrawableEntity.hpp"
#include "ImGuizmo.h"
DrawableEntity::DrawableEntity(GameObject* parent) : Component(parent), m_offset(1.0f){}

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
    //m_parent->GetComponent<Transform>()->getMatrix() + m_offset;

    glm::mat4 temp = m_parent->GetComponent<Transform>()->getMatrix() * m_offset;

    if(m_animator == nullptr)
    {
        //Yokai::getInstance().getModelManager()->DrawModel(m_modelID,m_parent->GetComponent<Transform>()->getMatrix());
        Yokai::getInstance().getModelManager()->DrawModel(m_modelID, temp);
    }
    else
    {
        //Yokai::getInstance().getModelManager()->DrawModel(m_modelID,m_parent->GetComponent<Transform>()->getMatrix(),m_animator->finalTransforms);
        Yokai::getInstance().getModelManager()->DrawModel(m_modelID,temp,m_animator->finalTransforms);
    }
  
}

unsigned int DrawableEntity::LoadModel(std::string filename)
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

	return m_modelID;
}

void DrawableEntity::SetAnimation(std::string animation)
{
    m_animator->setAnimation(animation);
}
void DrawableEntity::RenderGUI()
{
    float position[3];
	float rotation[3];
	float scale[3];
	if(ImGui::TreeNode("Model"))
	{
		ImGuizmo::DecomposeMatrixToComponents(&m_offset[0][0],&position[0],&rotation[0],&scale[0]);
		ImGui::DragFloat3("Position: ",&position[0],0.01f);
		ImGui::DragFloat3("Rotation: ",&rotation[0],0.01f);
		ImGui::DragFloat3("Scale: ",&scale[0],0.01f);
		ImGui::TreePop();
        ImGui::Separator();
		ImGuizmo::RecomposeMatrixFromComponents(&position[0],&rotation[0],&scale[0],&m_offset[0][0]);
	}
}
void DrawableEntity::SetOffset(glm::mat4 offset) 
{
    m_offset = offset;
}

glm::mat4 DrawableEntity::GetOffset() 
{
    return m_offset;
}

void DrawableEntity::SetModelID(unsigned int modelID)
{
	m_modelID = modelID;
}
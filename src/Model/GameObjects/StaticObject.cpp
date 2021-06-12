#include "StaticObject.hpp"

StaticObject::StaticObject(const std::string& modelName)
: m_physics(m_transform)
{
    modelID = ModelManager::getInstance().GetModelID(modelName);
}
StaticObject::~StaticObject(){
    m_physics.deleteCollider();
}
void StaticObject::draw()
{
    ModelManager::getInstance().DrawModel(modelID, m_transform.getMatrix());
}

void StaticObject::setCollider(float width, float height, float length)
{
	m_physics.registerAABB(ID,width, height, length);
    m_physics.getCollider()->SetBodyType(rp3d::BodyType::STATIC);
    m_physics.getCollider()->SetBounciness(0.0);

}

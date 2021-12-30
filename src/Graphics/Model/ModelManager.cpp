//
// Created by Charlie Sewell on 23/02/2021.
//

#include "Model/ModelManager.hpp"

ModelManager::ModelManager() 
{
    m_models.resize(100);
}

auto ModelManager::GetModelID(const std::string& filename) -> size_t
{ 
    auto id = m_modelIDtoName.find(filename);
    //stops files being loaded more then once
    if(id == m_modelIDtoName.end()){
        m_models[m_modelCount] = m_modelLoader.LoadModel(filename);
        m_modelIDtoName.emplace(filename, m_modelCount);
        m_modelCount++;
        return m_modelCount-1;
    }
    return(id->second);
}

Model* ModelManager::GetModel(size_t modelID)
{
    return(&m_models[modelID]);
}

void ModelManager::DrawModel(size_t id, glm::mat4 transform) 
{
    m_models[id].Draw(transform);
}
void ModelManager::DrawModel(size_t id, glm::mat4 transform, std::vector<glm::mat4> &finalTransforms)
{
   m_models[id].Draw(transform, finalTransforms);
}
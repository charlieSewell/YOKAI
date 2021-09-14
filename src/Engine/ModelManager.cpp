//
// Created by Charlie Sewell on 23/02/2021.
//

#include "Engine/ModelManager.hpp"

ModelManager::ModelManager() 
{
    models.resize(100);
}

auto ModelManager::GetModelID(const std::string& filename) -> size_t
{
    auto id = modelIDtoName.find(filename);
    //stops files being loaded more then once
    if(id == modelIDtoName.end()){
        models[modelCount] = modelLoader.loadModel(filename);
        modelIDtoName.emplace(filename,modelCount);
        modelCount++;
        return modelCount-1;
    }
    return(id->second);
}

std::shared_ptr<Model> ModelManager::GetModel(size_t modelID)
{
    return(std::make_shared<Model>(models[modelID]));
}

void ModelManager::DrawModel(size_t id, glm::mat4 transform) 
{
    models[id].Draw(transform);
}
void ModelManager::DrawModel(size_t id, glm::mat4 transform, std::vector<glm::mat4> &finalTransforms)
{
    //modelShader->useShader();
    //modelShader->setBool("isAnimated",true);
    //modelShader->setVecMat4("boneTrans",finalTransforms);
    //modelShader->setVec3("viewPos",EMS::getInstance().fire(ReturnVec3Event::getPlayerPosition));
    //models[id].Draw(transform);
}
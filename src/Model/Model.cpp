
#include "Model.hpp"

#include <utility>
Model::Model(std::vector<Mesh> meshes)
{
    this->meshes = std::move(meshes);
}
Model::Model(std::vector<Mesh> meshes, std::vector<Bone> bones, std::map<std::string, unsigned int> boneMap, Node rootNode, std::vector<SkeletalAnimation> animations, glm::mat4 globalInverseTransformation)
{
    this->meshes = std::move(meshes);
    this->bones = std::move(bones);
    this->rootNode = std::move(rootNode);
    this->boneMap = std::move(boneMap);
    this->animations = std::move(animations);
    this->globalInverseTransform = globalInverseTransformation;
}
void Model::Draw(glm::mat4 transform) 
{
    for(auto& mesh: meshes)
    {
        glm::mat4 model(1.0);
        //multiply parent by child transform
        model = transform* mesh.getTransform();
        Renderer::getInstance().AddToDraw(&mesh,model);
    }
}
void Model::Draw(glm::mat4 transform, std::vector<glm::mat4> &finalTransforms)
{
    for(auto& mesh: meshes)
    {
        glm::mat4 model(1.0);
        //multiply parent by child transform
        model = transform* mesh.getTransform();
        Renderer::getInstance().AddToDraw(&mesh,model,finalTransforms);
    }
}
SkeletalAnimation* Model::getAnimation(const std::string& name)
{
    for(auto& anim : animations)
    {
        if(anim.getName() == name)
        {
            return &anim;
        }
    }
    return nullptr;
}
Node Model::getRootNode()
{
    return rootNode;
}
bool Model::isAnimated()
{
    //if the array is empty it returns true which means the model isnt animated
    return !animations.empty();
}



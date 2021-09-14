
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
        AddToDraw(&mesh,model);
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
void Model::AddToDraw(Mesh* mesh, glm::mat4 model)
{
    DrawItem drawItem;
    drawItem.transform = model;
    drawItem.mesh = mesh;
    Renderer::getInstance().SubmitDraw(drawItem);
}



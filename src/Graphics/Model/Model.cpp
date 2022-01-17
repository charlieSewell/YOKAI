
#include "Model.hpp"

#include <utility>
Model::Model(std::vector<Mesh> meshes)
{
    this->m_meshes = std::move(meshes);
}
Model::Model(std::vector<Mesh> meshes, std::vector<Bone> bones, std::map<std::string, unsigned int> boneMap, Node rootNode, std::vector<SkeletalAnimation> animations, glm::mat4 globalInverseTransformation)
{
    this->m_meshes = std::move(meshes);
    this->m_bones = std::move(bones);
    this->m_rootNode = std::move(rootNode);
    this->m_boneMap = std::move(boneMap);
    this->m_animations = std::move(animations);
    this->m_globalInverseTransform = globalInverseTransformation;
}
void Model::Draw(glm::mat4 transform) 
{
    for(auto& mesh: m_meshes)
    {
        glm::mat4 model{1.0f};
        //multiply parent by child transform
        model = transform* mesh.getTransform();
        Renderer::getInstance().AddToDraw(&mesh,model);
    }
}
void Model::Draw(glm::mat4 transform, std::vector<glm::mat4> &finalTransforms)
{
    for(auto& mesh: m_meshes)
    {
        glm::mat4 model{1.0f};
        //multiply parent by child transform
        model = transform* mesh.getTransform();
        Renderer::getInstance().AddToDraw(&mesh,model,finalTransforms);
    }
}
SkeletalAnimation* Model::GetAnimation(const std::string& name)
{
    for(auto& anim : m_animations)
    {
        if(anim.GetName() == name)
        {
            return &anim;
        }
    }
    return nullptr;
}
Node Model::GetRootNode()
{
    return m_rootNode;
}
bool Model::IsAnimated()
{
    //if the array is empty it returns true which means the model isnt animated
    return !m_animations.empty();
}



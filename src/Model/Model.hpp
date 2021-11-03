//
// Created by Charlie on 12/01/2021.
//
#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Model/SkeletalAnimation.hpp"
#include "Renderer/Renderer.hpp"
/**
 * @struct Node
 * @brief Struct to hold info about a assimp node
 */
struct Node
{
    ///Transform of a node
    glm::mat4 transform = {};
    ///Name of a node
    std::string name;
    ///Children Nodes
    std::vector<Node> children = {};
    ///Count of children
    unsigned int childrenCount = 0;
};
/**
 * @struct Bone
 * @brief Struct to hold info about a bone
 */
struct Bone
{
    ///Bones offset from position of model
    glm::mat4 offset = glm::mat4(1.0f);
    ///Transform of the bone
    glm::mat4 transform = glm::mat4(1.0f);
};
/**
 * @class Model
 * @brief A class to hold model Data
 */
class Model
{
  public:
    /**
     * @brief Default constructor for a model
     */
    Model() = default;
    /**
     * @brief Constructor for a model that takes in a list of meshes
     * @param vector<Mesh> - meshes
     */
    Model(std::vector<Mesh> meshes);
    /**
     * @brief Constructor for a model that is animated
     * @param vector<Mesh> - meshes
     * @param vector<Bone> - bones
     * @param map<string,unsigned int> - boneMap
     * @param Joint - rootNode
     * @param vector<SkeletalAnimation> - animations
     */
    Model(std::vector<Mesh> meshes, std::vector<Bone> bones, std::map<std::string, unsigned int> boneMap, Node rootJoint, std::vector<SkeletalAnimation> animations, glm::mat4 globalInverseTransform);
    /**
     * @brief Draws a mesh
     * @param Shader& - shader
     * @param mat4 - transform
     */
    void Draw(glm::mat4 transform);
    /**
     * @brief Draws a mesh model thats animated
     * @param Shader& - shader
     * @param mat4 - transform
     */
    void Draw(glm::mat4 transform, std::vector<glm::mat4> &finalTransforms);
    /**
     * @brief Gets animation by Name
     * @param name
     * @return SkeletalAnimation*
     */
    SkeletalAnimation* GetAnimation(const std::string& name);
    /**
     * @brief Gets the size of the bones array
     * @return
     */
    int GetBonesSize(){return m_bones.size();}
    /**
     * @brief Gets the root node of the model
     * @return
     */
    Node GetRootNode();
    /**
     * @brief Gets the map of string to bone ID
     * @return
     */
    std::map<std::string, unsigned int>* GetBoneMap(){return &m_boneMap;}
    /**
     * @brief Returns the vector of bones
     * @return mat4
     */
    std::vector<Bone>* GetBones(){return &m_bones;}
    /**
     * @brief Get the Meshes array
     * @return std::vector<Mesh>* 
     */
    std::vector<Mesh>* GetMeshes(){return &m_meshes;}
    /**
     * @brief gets the global inverse transform
     * @return mat4
     */
    glm::mat4 GetGlobalInverseTransform(){return m_globalInverseTransform;}
    /**
     * @brief is the model animated
     * @return bool
     */
    bool IsAnimated();
  private:
    ///Global transform
    glm::mat4 m_globalInverseTransform{};
    ///list of models meshes
    std::vector<Mesh> m_meshes;
    ///list of models bones
    std::vector<Bone> m_bones;
    ///map of bone names to index
    std::map<std::string, unsigned int> m_boneMap;
    ///Root node of scene
    Node m_rootNode;
    ///Animations
    std::vector<SkeletalAnimation> m_animations;
};


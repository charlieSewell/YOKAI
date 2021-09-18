//
// Created by Charlie on 12/01/2021.
//
#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Renderer/Shader.hpp"
#include "Model/Mesh.hpp"
#include "Model/SkeletalAnimation.hpp"

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
    void Draw(Shader &shader, glm::mat4 transform);
    /**
     * @brief Gets animation by Name
     * @param name
     * @return SkeletalAnimation*
     */
    SkeletalAnimation* getAnimation(const std::string& name);
    /**
     * @brief Gets the size of the bones array
     * @return
     */
    int getBonesSize(){return bones.size();}
    /**
     * @brief Gets the root node of the model
     * @return
     */
    Node getRootNode();
    /**
     * @brief Gets the map of string to bone ID
     * @return
     */
    std::map<std::string, unsigned int>* getBoneMap(){return &boneMap;}
    /**
     * @brief Returns the vector of bones
     * @return mat4
     */
    std::vector<Bone>* getBones(){return &bones;}
    /**
     * @brief Get the Meshes array
     * @return std::vector<Mesh>* 
     */
    std::vector<Mesh>* getMeshes(){return &meshes;}
    /**
     * @brief gets the global inverse transform
     * @return mat4
     */
    glm::mat4 getGlobalInverseTransform(){return globalInverseTransform;}

  private:
    ///Global transform
    glm::mat4 globalInverseTransform{};
    ///list of models meshes
    std::vector<Mesh> meshes;
    ///list of models bones
    std::vector<Bone> bones;
    ///map of bone names to index
    std::map<std::string, unsigned int> boneMap;
    ///Root node of scene
    Node rootNode;
    ///Animations
    std::vector<SkeletalAnimation> animations;
};


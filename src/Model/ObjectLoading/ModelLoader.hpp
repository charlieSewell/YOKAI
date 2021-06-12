//
// Created by Charlie Sewell on 1/04/2021.
//

#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/type_ptr.hpp>
#include "Model/Model.hpp"
#include "Model/SkeletalAnimation.hpp"
#include "Controller/TextureManager.hpp"
/** @class ModelLoader
 *  @brief Class that loads models
 */

class ModelLoader 
{
  public:
    /**
     * @brief Loads a model and returns a vector of meshes
     * @param string - filename
     * @return vector<Mesh>
     */
    Model loadModel(const std::string& filename);

  private:
    ///string that stores the directory
    std::string directory;
    /**
     * @brief processes and indivudial node in the scene
     * @param vector<Mesh> - meshes
     * @param aiNode* - node
     * @param const aiScene* - scene
     * @param mat4 - transform
     */
    void processNode(std::vector<SkeletalAnimation> &animations, std::vector<Mesh> &meshes,
                     std::vector<Bone> &bones,
                     std::map<std::string, unsigned int> &boneMap, aiNode *node,
                     const aiScene *scene, glm::mat4 transform);
    /**
     * @brief Processes a singular mesh of a model
     * @param aiMesh* - mesh
     * @param const aiScene* - scene
     * @param mat4 - transform
     * @return Mesh
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene,glm::mat4 transform);
    /**
     * @brief Loads the Textures for a model
     * @param aiMaterial* - mat
     * @param aiTextureType - type
     * @param string - typeName
     * @return vector<ModelTexture>
     */
    std::vector<ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    ///Finds the root node of the skeleton
    aiNode* findRootNode(aiNode* node, aiMesh* mesh);
    ///Loads in the Node Heirachy
    void loadAnimNodes(aiNode* node,aiMesh* mesh);
    ///Creates a node heirachy given a aiNode
    Node loadNodeHeirachy(aiNode *root);
    ///Adds the Bone Data
    void addBoneData(unsigned int BoneID, float Weight);
    ///Loads a models animations
    void loadAnimations(std::vector<SkeletalAnimation> &animations, const aiScene *scene);
    ///Loads the bones of a mesh
    void loadBones(std::vector<Mesh> &meshes, std::vector<Bone> &bones,
                   std::map<std::string,unsigned int> &boneMap,
                   unsigned int meshIndex, const aiMesh *mesh);
    ///List of textures currently loaded for a model
    std::vector<ModelTexture> textures_loaded;
    /// Number of bones in current model
    int numBones = 0;
    ///Root animation node
    Node rootAnimNode;
};

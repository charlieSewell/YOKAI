//
// Created by Charlie Sewell on 1/04/2021.
//

#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/GltfMaterial.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Model/Model.hpp"
#include "Renderer/TextureManager.hpp"
#include "CalcTangent.hpp"
#include "spdlog/spdlog.h"


/** 
 *  @class ModelLoader
 *  @brief Class that loads models
 */

class ModelLoader 
{
  public:
    ModelLoader();
    ~ModelLoader();
    /**
     * @brief Loads a model and returns a vector of meshes
     * @param string - filename
     * @return vector<Mesh>
     */
    Model LoadModel(const std::string& filename);

  private:
    /**
     * @brief processes and indivudial node in the scene
     * @param vector<Mesh> - meshes
     * @param aiNode* - node
     * @param const aiScene* - scene
     * @param mat4 - transform
     */
    void ProcessNode(std::vector<SkeletalAnimation> &animations, std::vector<Mesh> &meshes,
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
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene,glm::mat4 transform);
    /**
     * @brief Loads the Textures for a model
     * @param aiMaterial* - mat
     * @param aiTextureType - type
     * @param string - typeName
     * @return vector<ModelTexture>
     */
    std::vector<ModelTexture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    /**
     * @brief Finds the Root node of a model
     * @param node 
     * @param mesh 
     * @return aiNode* 
     */
    aiNode* FindRootNode(aiNode* node, aiMesh* mesh);
    /**
     * @brief Loads each animation for a node
     * @param node 
     * @param mesh 
     */
    void LoadAnimNodes(aiNode* node,aiMesh* mesh);
    /**
     * @brief Loads the Node Heirachy of a model
     * @param root 
     * @return Node 
     */
    Node LoadNodeHeirachy(aiNode *root);
    /**
     * @brief Adds the bone data of a model
     * @param BoneID 
     * @param Weight 
     */
    void AddBoneData(unsigned int BoneID, float Weight);
    /**
     * @brief Loads the Animations of a model
     * @param animations 
     * @param scene 
     */
    void LoadAnimations(std::vector<SkeletalAnimation> &animations, const aiScene *scene);
    /**
     * @brief Loads the Bones of a model
     * @param meshes 
     * @param bones 
     * @param boneMap 
     * @param meshIndex 
     * @param mesh 
     */
    void LoadBones(std::vector<Mesh> &meshes, std::vector<Bone> &bones,
                   std::map<std::string,unsigned int> &boneMap,
                   unsigned int meshIndex, const aiMesh *mesh);

    /**
     * @brief Loads a Material
     * @param material 
     * @param dir 
     * @return Material 
     */
    Material ModelLoader::LoadMaterial(const aiMaterial* material);
    ///List of textures currently loaded for a model
    std::vector<ModelTexture> m_textures_loaded;
    /// Number of bones in current model
    int m_numBones = 0;
    ///Root animation node
    Node m_rootAnimNode;
    ///string that stores the directory
    std::string m_directory;
    ///Texture manager
    TextureManager m_textureManager;
    ///Model Importer
    Assimp::Importer m_importer;
    ///Dummy Textures for when one isnt present
    std::vector<Texture> m_dummyTextures;
    CalcTangents m_tangentCalculator;
};

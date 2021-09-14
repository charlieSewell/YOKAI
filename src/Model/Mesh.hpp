//
// Created by Charlie Sewell on 12/01/2021.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Renderer/DataTypes.hpp"

/**
 * @class Mesh
 * @brief Class that defines a mesh
 */
class Mesh
{
  public:
    /**
     * @brief Default constructor for mesh
     */
    Mesh(){}
    /**
     * @brief Constructor for a mesh
     * @param const vector<Vertex>& - vertices
     * @param const vector<unsigned int>& - indices
     * @param const vector<ModelTexture>& - textures
     * @param mat4& - transform
     */
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<ModelTexture> &textures,glm::mat4 &transform);
    /**
     * @brief returns a list of vertices
     * @return vector<Vertex>
     */
    std::vector<Vertex>* getVertices(){return &vertices;}
    /**
     * @brief returns a list of indices
     * @return vector<unsigned int>
     */
    std::vector<unsigned int>* getIndices(){return &indices;}
    /**
     * @brief returns a list of textures
     * @return vector<ModelTexture>
     */
    std::vector<ModelTexture> getTextures(){return textures;}
    /**
     * @brief returns the transform
     * @return mat4
     */
    glm::mat4 getTransform(){return transform;}

    /**
     * @brief Sets up the mesh
     */
    void SetupMesh();

    void addBoneData(unsigned int vertexID,unsigned int boneID, float weight);

    std::shared_ptr<VertexArrayBuffer> GetVAO(){return VAO;}
  private:
    ///Pointer to the Mesh vertex array
    std::shared_ptr<VertexArrayBuffer> VAO;
    ///mesh vertices
    std::vector<Vertex> vertices;
    ///mesh indices
    std::vector<unsigned int> indices;
    ///mesh textures
    std::vector<ModelTexture> textures;
    ///mesh transform
    glm::mat4 transform;
};

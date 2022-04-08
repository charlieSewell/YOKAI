#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Renderer/DataTypes.hpp"
#include "Material.hpp"

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
    Mesh(const std::vector<Vertex> &vertices, const std::vector<uint16_t> &indices, glm::mat4 &transform, Material material);
    /**
     * @brief returns a list of vertices
     * @return vector<Vertex>
     */
    std::vector<Vertex>* getVertices(){return &m_vertices;}
    /**
     * @brief returns a list of indices
     * @return vector<unsigned int>
     */
    std::vector<uint16_t>* getIndices(){return &m_indices;}
    /**
     * @brief returns the transform
     * @return mat4
     */
    glm::mat4 getTransform(){return m_transform;}
    /**
     * @brief Sets up the mesh
     */
    void SetupMesh();
    /**
     * @brief Adds bone data to the mesh
     * @param vertexID 
     * @param boneID 
     * @param weight 
     */
    void addBoneData(unsigned int vertexID, uint16_t boneID, float weight);
    /**
     * @brief Get the VAO for this mesh
     * @return std::shared_ptr<VertexArrayBuffer> 
     */
    std::shared_ptr<VertexArrayBuffer> GetVAO(){return m_VAO;}

    /**
     * @brief Gets the Material for the mesh
     * @return Material
     */
    Material GetMaterial(){return m_material;}
  private:
    ///Pointer to the Mesh vertex array
    std::shared_ptr<VertexArrayBuffer> m_VAO = nullptr;
    ///mesh vertices
    std::vector<Vertex> m_vertices = {};
    ///mesh indices
    std::vector<uint16_t> m_indices = {};
    ///mesh material
    Material m_material;
    ///mesh transform
    glm::mat4 m_transform = {};
};

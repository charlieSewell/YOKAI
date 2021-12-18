//
// Created by Charlie Sewell on 12/01/2021.
//
#include "Mesh.hpp"
#include <glm/gtx/string_cast.hpp>
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<ModelTexture> &textures, glm::mat4 &transform)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->transform = transform;
}

void Mesh::SetupMesh()
{
    VAO = VertexArrayBuffer::Create(this->vertices,this->indices);
}

void Mesh::addBoneData(unsigned int vertexID,unsigned int boneID, float weight)
{
    for (int i = 0 ; i < 4 ; ++i)
    {
        if (vertices.at(vertexID).boneWeights[i] == 0.0)
        {
            vertices.at(vertexID).boneIDs[i] = boneID;
            vertices.at(vertexID).boneWeights[i] = weight;
            return;
        }
    }
}
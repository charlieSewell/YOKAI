#include "Mesh.hpp"
#include <glm/gtx/string_cast.hpp>
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint16_t> &indices, glm::mat4 &transform, Material material)
{
    this->m_vertices = vertices;
    this->m_indices = indices;
    this->m_transform = transform;
    m_material = material;
}

void Mesh::SetupMesh()
{
    m_VAO = VertexArrayBuffer::Create(this->m_vertices,this->m_indices);
}

void Mesh::addBoneData(unsigned int vertexID, uint16_t boneID, float weight)
{
    for (int i = 0 ; i < 4 ; ++i)
    {
        if (m_vertices.at(vertexID).boneWeights[i] == 0.0)
        {
            m_vertices.at(vertexID).boneIDs[i] = boneID;
            m_vertices.at(vertexID).boneWeights[i] = weight;
            return;
        }
    }
}
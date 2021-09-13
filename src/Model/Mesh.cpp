//
// Created by Charlie Sewell on 12/01/2021.
//
#include "Mesh.hpp"
#include "Engine/Yokai.hpp"
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

 const void Mesh::Draw(Shader &shader)
 {
     unsigned int diffuseNr = 1;
     unsigned int specularNr = 1;

     for(size_t i = 0; i < textures.size(); i++)
     {
         TextureManager::getInstance().getTexture(textures[i].texture)->Bind(i);
         std::string number;
         std::string name = textures[i].type;
         if(name == "texture_diffuse")
             number = std::to_string(diffuseNr++);
         else if(name == "texture_specular")
             number = std::to_string(specularNr++);

         shader.setFloat(("material." + name + number).c_str(), static_cast<float>(i));
     }
     // draw mesh
     auto& engine = Yokai::getInstance();
     engine.renderer.DrawArrays(*VAO,indices.size());

    // Reset to defaults
	for (size_t i = 0; i < this->textures.size(); i++) {
		TextureManager::getInstance().getTexture(textures[i].texture)->UnBind(i);
	}
     
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
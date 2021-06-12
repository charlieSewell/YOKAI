//
// Created by charl on 4/03/2021.
//

#ifndef ICT397_GAME_ENGINE_CHUNK_HPP
#define ICT397_GAME_ENGINE_CHUNK_HPP

#include <vector>
#include <memory>
#include "View/Renderer/DataTypes.hpp"
#include "View/Renderer/Shader.hpp"
#include "View/Renderer/Renderer.hpp"
/**
 * @class Chunk
 * @brief A class that holds a singular chunk
 */
class Chunk 
{
  public:
    /**
     * @brief Constructs a Chunk Objects
     */
    Chunk() = default;
    /**
     * @brief Constructs a chunks mesh
     * @param vector<Vertex> - vertices
     * @param vector<unsigned int> - indices
     */
    void SetupChunk(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    /**
     * @brief Draws a chunk
     * @param Shader& - shader
     */
    void DrawChunk(Shader &shader);
    /**
     * @brief Gets the ID of a chunk
     * @return unsigned int - ID
     */
    unsigned int GetID(){return chunkID;}

  private:
    ///pointer to the mesh
    std::shared_ptr<VertexArrayBuffer> VAO;
    ///number of points in the mesh
    size_t indicesSize;
    ///chunk ID
    unsigned int chunkID;
};

#endif // ICT397_GAME_ENGINE_CHUNKDATA_HPP

#pragma once
#include <vector>
#include <map>
#include "Model/Chunk.hpp"
#include "Controller/Factory/TerrainFactory.hpp"
#include "Controller/TextureManager.hpp"
/**
 * @class TerrainManager
 * @brief Responsible for managing terrain
 */
class TerrainManager 
{
  public:
    /**
     * @brief Default Constructor for Terrain Factory
     */
    TerrainManager() = default;
    /*!
     * @brief Initialises the manager
     */
    void Init();

    /*!
     * @brief Draws chunks of terrain
     * @param vec3 - viewPos
     */
    void Draw(glm::vec3 viewpos);
    /**
     * @brief sets the terrain Textures;
     * @param vector<unsigned int> - texturesToSet
     */
    void setTerrainTexture(std::vector<unsigned int> texturesToSet);
    /**
     * @brief Sets the Sand Height
     * @param int - height
     */
    void setSandHeight(int height){sandHeight = height;}
    /**
     * @brief Sets the Snow Height
     * @param int - height
     */
    void setSnowHeight(int height){snowHeight = height;}
    /**
     * @brief Sets the Grass Height
     * @param int - height
     */
    void setGrassHeight(int height){grassHeight = height;}
  private:
    /*!
     * @brief Creates terrain
     */
    void CreateTerrain();

    /// Size of chunk, maximum key value
    int chunkSize{},maxKey{};

    /// Shader pointer
    Shader* terrainShader{};

    /// Map of chunks
    std::map<std::pair<int,int>,Chunk> chunks;
    ///Array of textures to use
    std::vector<unsigned int> textures;
    ///heights of the textures
    int sandHeight{},grassHeight{},snowHeight{};
    ///textures
    std::string sandTexture, snowTexture, grassTexture, detailTexture;
};

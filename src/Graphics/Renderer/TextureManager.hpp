#pragma once
#include "Renderer/DataTypes.hpp"
#include <iostream>
#include <map>
/**
 * @class TextureManager
 * @brief Manages all textures in the engine
 */
class TextureManager{
public:
    /**
     * @brief Default private constructor
     */
    TextureManager();
    /**
     * @brief Loads a texture given a filename
     * @param textureName
     * @return textureID
     */
    std::shared_ptr<Texture> LoadTexture(const std::string& textureName, const bool srgb = false);
    /**
     * @brief Gets a texture from an ID
     * @param textureID
     * @return Texture*
     */
    std::shared_ptr<Texture> GetTexture(unsigned int textureID);
    /**
     * @brief Replace a texture with a new one
     * @param slot
     * @param newTexturePath
     */
    void ReplaceTexture(size_t slot,const std::string& newTexturePath);
private:
    ///map of textures to IDs
    std::map<unsigned int,std::pair<std::string,std::shared_ptr<Texture>>> m_textures;
    ///texture count
    unsigned int m_textureCount;
};

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
     * @brief returns the instance of the texture manager
     * @return TextureManager&
     */
    static TextureManager &getInstance();
    /**
     * @brief Loads a texture given a filename
     * @param textureName
     * @return textureID
     */
    unsigned int loadTexture(const std::string& textureName);
    /**
     * @brief Gets a texture from an ID
     * @param textureID
     * @return Texture*
     */
    std::shared_ptr<Texture> getTexture(unsigned int textureID);
    /**
     * @brief Replace a texture with a new one
     * @param slot
     * @param newTexturePath
     */
    void replaceTexture(size_t slot,const std::string& newTexturePath);
private:
    /**
     * @brief Default private constructor
     */
    TextureManager();
    ///map of textures to IDs
    std::map<unsigned int,std::pair<std::string,std::shared_ptr<Texture>>> textures;
    ///texture count
    unsigned int textureCount;
};

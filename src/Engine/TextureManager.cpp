
#include "TextureManager.hpp"
TextureManager::TextureManager() {
    textureCount = 0;
}
TextureManager& TextureManager::getInstance()
{
    static TextureManager instance;
    return instance;
}
std::shared_ptr<Texture> TextureManager::getTexture(unsigned int textureID)
{
    return textures.at(textureID).second;
}
unsigned int TextureManager::loadTexture(const std::string &textureName)
{
    for(auto& texture : textures)
    {
        if(texture.second.first == textureName)
        {
            return texture.first;
        }
    }
    textures.emplace(textureCount,std::pair(textureName,Texture::Create(textureName)));
    textureCount++;
    return(textureCount -1);
}
void TextureManager::replaceTexture(size_t slot, const std::string &newTexturePath)
{
    textures.at(slot) = std::pair(newTexturePath,Texture::Create(newTexturePath));
}
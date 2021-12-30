
#include "TextureManager.hpp"
TextureManager::TextureManager() {
    m_textureCount = 0;
}
std::shared_ptr<Texture> TextureManager::GetTexture(unsigned int textureID)
{
    return m_textures.at(textureID).second;
}
std::shared_ptr<Texture> TextureManager::LoadTexture(const std::string &textureName)
{
    for(auto& texture : m_textures)
    {
        if(texture.second.first == textureName)
        {
            return(m_textures.at(texture.first).second);
        }
    }
    m_textures.emplace(m_textureCount,std::pair(textureName,Texture::Create(textureName)));
    m_textureCount++;
    return(m_textures.at(m_textureCount-1).second);
}
void TextureManager::ReplaceTexture(size_t slot, const std::string &newTexturePath)
{
    m_textures.at(slot) = std::pair(newTexturePath,Texture::Create(newTexturePath));
}
//
// Created by charl on 4/03/2021.
//

#include "TerrainManager.hpp"
#include <spdlog/spdlog.h>
void TerrainManager::setTerrainTexture(std::vector<unsigned int> texturesToSet) {
    textures = std::move(texturesToSet);
}
void TerrainManager::Init() 
{
    chunkSize = 100;
    maxKey = static_cast<int>(floor(TerrainFactory::getInstance().getTerrainSize()/100));
    CreateTerrain();
    terrainShader = new Shader("content/Shaders/terrainVertex.vert","content/Shaders/terrainFragment.frag");
    terrainShader->useShader();
    terrainShader->setVec3("skyColor",glm::vec3(0.05,0.05,0.05));
    terrainShader->setVec3("lightColor",glm::vec3(1.0,1.0,1.0));
    terrainShader->setVec3("lightPos",glm::vec3(maxKey*chunkSize/2,400,maxKey*chunkSize/2));
    terrainShader->setFloat("lightLinear",0.002);
    terrainShader->setFloat("lightQuadratic",0.000004);
    terrainShader->setInt("grassTexture",0);
    terrainShader->setInt("sandTexture",1);
    terrainShader->setInt("snowTexture",2);
    terrainShader->setInt("detailMap",3);
    terrainShader->setFloat("sandHeight",static_cast<float>(sandHeight));
    terrainShader->setFloat("grassHeight",static_cast<float>(grassHeight));
    terrainShader->setFloat("snowHeight",static_cast<float>(snowHeight));
    SPDLOG_INFO("Initialised Terrain Manager");
}

void TerrainManager::CreateTerrain() 
{
    for( int x =0; x < maxKey;x++)
    {
        for (int y = 0; y < maxKey; y++) 
        {
            std::pair<int,int> key(x,y);
            chunks.emplace(key,TerrainFactory::getInstance().SetupChunk(x*100,y*100,100));
        }
    }

}

void TerrainManager::Draw(glm::vec3 viewpos) 
{

    terrainShader->useShader();
    terrainShader->setVec3("viewPos",viewpos);
    terrainShader->setMat4("projection",EMS::getInstance().fire(ReturnMat4Event::getPerspective));
    terrainShader->setMat4("view",EMS::getInstance().fire(ReturnMat4Event::getViewMatrix));
    terrainShader->setMat4("model",glm::mat4(1.0));

    auto& textureManager = TextureManager::getInstance();
    textureManager.getTexture(textures[0])->Bind(0);
    textureManager.getTexture(textures[1])->Bind(1);
    textureManager.getTexture(textures[2])->Bind(2);
    textureManager.getTexture(textures[3])->Bind(3);
    for (int x = 0; x < maxKey; x++)
    {
        for (int y = 0; y < maxKey; y++) 
        {
            std::pair<int, int> key(x, y);
            chunks.at(key).DrawChunk(*terrainShader);
        }
    }
}

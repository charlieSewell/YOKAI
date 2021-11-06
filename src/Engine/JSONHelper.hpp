#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "Export.hpp"
#include "Engine/GameObjectManager.hpp"
#include "Renderer/LightManager.hpp"
namespace YOKAI_PARSE 
{   
    /**
     * @brief Loads a Scene File
     * @param file 
     * @param objectManager 
     * @param lightManager 
     */
    void YOKAI_API LoadScene(std::string file, GameObjectManager &objectManager, LightManager &lightManager);
    /**
     * @brief Saves a Scene File
     * @param file 
     * @param objectManager 
     * @param lightManager 
     */
    void YOKAI_API SaveScene(std::string file, GameObjectManager objectManager,  LightManager lightManager);
}

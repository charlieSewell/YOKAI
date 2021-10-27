#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "Export.hpp"
#include "Engine/GameObjectManager.hpp"
#include "Renderer/LightManager.hpp"
namespace YOKAI_PARSE 
{
    void YOKAI_API LoadScene(std::string file, GameObjectManager &objectManager, LightManager &lightManager);
    void YOKAI_API SaveScene(std::string file, GameObjectManager objectManager,  LightManager lightManager);

}

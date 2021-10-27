#include "JSONHelper.hpp"
#include <fstream>
#include <vector>
#include <string>
void YOKAI_PARSE::LoadScene(std::string file, GameObjectManager &objectManager, LightManager &lightManager)
{
    nlohmann::json j = {};
    std::ifstream input(file);
    
    if (!input.is_open()) 
    {
        std::string error("Failed to load JSON file at: " + file);
        SPDLOG_ERROR(error);
    }
    
    input >> j;

    for (auto &object  : j.at("Objects"))
    {
        auto ObjectToFill = objectManager.GetObject(object.at("ID").get<unsigned int>());
        ObjectToFill->Deserialise(object);
    }
    lightManager.Deserialise(j);

}
void YOKAI_PARSE::SaveScene(std::string file, GameObjectManager objectManager, LightManager lightManager)
{
    nlohmann::json j = {};
    std::ofstream output(file);
    
    j = nlohmann::json::object();
    
    objectManager.Serialise(j);
    lightManager.Serialise(j);
    output << std::setw(4) << j << std::endl;
    //input >> j;

}


#pragma once
#include "Export.hpp"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
namespace glm
{
    /**
     * @brief Translates a vec3 to json format
     * @param j 
     * @param p 
     */
    void YOKAI_API to_json(nlohmann::json& j, const vec3& p);
    /**
     * @brief Translates a vec3 from json format
     * @param j 
     * @param p 
     */
    void YOKAI_API from_json(const nlohmann::json& j, vec3& p);
    /**
     * @brief Translates a vec4 to json format
     * @param j 
     * @param p 
     */
    void YOKAI_API to_json(nlohmann::json& j, const vec4& p);
    /**
     * @brief Translates a vec4 from json format
     * @param j 
     * @param p 
     */
    void YOKAI_API from_json(const nlohmann::json& j, vec4& p);
}
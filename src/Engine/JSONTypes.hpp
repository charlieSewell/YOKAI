#pragma once
#include "Export.hpp"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
namespace glm
{
    void YOKAI_API to_json(nlohmann::json& j, const vec3& p);
    void YOKAI_API from_json(const nlohmann::json& j, vec3& p);
    void YOKAI_API to_json(nlohmann::json& j, const vec4& p);
    void YOKAI_API from_json(const nlohmann::json& j, vec4& p);
}
#include "JSONTypes.hpp"
void glm::to_json(nlohmann::json& j, const vec3& vec)
{
    j = nlohmann::json::object();
    j["x"] = vec.x;
    j["y"] = vec.y;
    j["z"] = vec.z;
}
void glm::from_json(const nlohmann::json& j, vec3& vec)
{
    j.at("x").get_to(vec.x);
	j.at("y").get_to(vec.y);
	j.at("z").get_to(vec.z);
}
void glm::to_json(nlohmann::json& j, const vec4& vec)
{
    j = nlohmann::json::object();
    j["x"] = vec.x;
    j["y"] = vec.y;
    j["z"] = vec.z;
    j["w"] = vec.w;
}
void glm::from_json(const nlohmann::json& j, vec4& vec)
{
    j.at("x").get_to(vec.x);
	j.at("y").get_to(vec.y);
	j.at("z").get_to(vec.z);
    j.at("w").get_to(vec.w);
}
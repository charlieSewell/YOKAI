#include "LightManager.hpp"
LightManager::LightManager()
{
    m_LightCount = 0;
}
unsigned int LightManager::AddLight(glm::vec3 position, glm::vec3 color, float radius)
{
    glm::vec3 power = color * radius;
    m_Lights.push_back({position,power});
    m_LightCount++;
    return m_LightCount -1;
}
unsigned int LightManager::AddLight(PointLight light)
{
    m_Lights.push_back(light);
    m_LightCount++;
    return m_LightCount -1;
}
void LightManager::DeleteLight(unsigned int _lightIndex)
{
    //NOT IMPLIMENTED
}
PointLight* LightManager::GetLight(unsigned int lightIndex)
{
    return (&m_Lights[lightIndex]);
}
void LightManager::UpdateLights()
{
    Renderer::getInstance().UpdateLights(m_Lights);
}
void LightManager::Clear()
{
    m_LightCount = 0;
    m_Lights.clear();
    Renderer::getInstance().ResetLightsBuffer();
}
void LightManager::RenderGUI()
{
    ImGui::Begin("Lighting Manager");
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float);
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_HDR);
    for(size_t i=0; i < m_Lights.size();i++)
    {
        glm::vec3 color;
        float radius;
        ImGui::PushID(i);
        if(ImGui::TreeNode("Point Light"))
        {
            ImGui::DragFloat3("Position: ", &m_Lights[i].position[0], 0.1f);
            ImGui::ColorEdit3("Color", &color[0]);
            ImGui::DragFloat("Size: ", &radius, 0.1f);
            if(ImGui::Button("Delete Light")){
                DeleteLight(i);
            }
            ImGui::TreePop();
        }
        

        ImGui::PopID();
    }
    if(ImGui::Button("Add Light")){
        AddLight(glm::vec3{4.0f,3.0f,1.0f}, glm::vec3{1.0f}, 1.0f);
    }
    ImGui::End();
}
void LightManager::Serialize(nlohmann::json &j)
{
    j["Lights"] = nlohmann::json::array();
    for(auto& light : m_Lights)
    {
        glm::vec3 color = glm::normalize(light.flux);
        float radius = glm::length(light.flux);
        nlohmann::json temp = nlohmann::json::object();
        temp["Color"] = color;
        temp["Position"] = light.position;
        temp["Radius"] = radius;
        j["Lights"].push_back(temp);
    }
}
void LightManager::Deserialize(const nlohmann::json &j)
{
    for (auto &light : j.at("Lights"))
    {
        AddLight( light.at("Color").get<glm::vec3>(),light.at("Position").get<glm::vec3>(),light.at("Radius").get<float>());
    }
}

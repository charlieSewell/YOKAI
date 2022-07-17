#include "LightManager.hpp"
LightManager::LightManager()
{
    m_LightCount = 0;
}
unsigned int LightManager::AddLight(glm::vec3 position, glm::vec3 color, float radius)
{
    m_Lights.push_back({position,color,radius});
    m_LightCount++;
    return m_LightCount -1;
}
unsigned int LightManager::AddLight(PointLight light)
{
    m_Lights.push_back(light);
    m_LightCount++;
    return m_LightCount -1;
}
void LightManager::DeleteLight(unsigned int)
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
        ImGui::PushID(i);
        if(ImGui::TreeNode("Point Light"))
        {
            ImGui::DragFloat3("Position: ", &m_Lights[i].position[0], 0.1f);
            ImGui::ColorEdit3("Color", &m_Lights[i].flux[0],ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_Float);
            ImGui::DragFloat("Size: ", &m_Lights[i].radius, 0.1f);
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
        nlohmann::json temp = nlohmann::json::object();
        temp["Color"] = light.flux;
        temp["Position"] = light.position;
        temp["Radius"] = light.radius;
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

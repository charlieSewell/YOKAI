#include "LightManager.hpp"
LightManager::LightManager()
{
    m_LightCount = 0;
}
unsigned int LightManager::AddLight(glm::vec4 color, glm::vec4 position, glm::vec4 paddingAndRadius)
{
    PointLight light;
    light.color = color;
    light.position = position;
    light.paddingAndRadius = paddingAndRadius;
    m_Lights.push_back(light);
    m_LightCount++;
    return m_LightCount -1;
}
void LightManager::DeleteLight(unsigned int lightIndex)
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
void LightManager::RenderGUI()
{
    ImGui::Begin("Lighting Manager");
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float);
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_HDR);
    for(int i=0; i < m_Lights.size();i++)
    {
        glm::vec4 test;
        ImGui::PushID(i);
        if(ImGui::TreeNode("Point Light"))
        {
            ImGui::DragFloat3("Position: ",&m_Lights[i].position[0],0.1f);
            ImGui::ColorEdit4("Color", &m_Lights[i].color[0]);
            ImGui::DragFloat("Size: ",&m_Lights[i].paddingAndRadius[3],0.1f);
            if(ImGui::Button("Delete Light")){
                DeleteLight(i);
            }
            ImGui::TreePop();
        }
        

        ImGui::PopID();
    }
    if(ImGui::Button("Add Light")){
        AddLight(glm::vec4{4.0f,3.0f,1.0f,1.0f},glm::vec4{glm::vec3(0.0f),1.0f},glm::vec4{0.0f,0.0f,0.0f,30.0f});
    }
    ImGui::End();
}
void LightManager::Serialise(nlohmann::json &j)
{
    j["Lights"] = nlohmann::json::array();
    for(auto& light : m_Lights)
    {
        nlohmann::json temp = nlohmann::json::object();
        temp["Color"] = light.color;
        temp["Position"] = light.position;
        temp["PaddingAndRadius"] = light.paddingAndRadius;
        j["Lights"].push_back(temp);
    }
}
void LightManager::Deserialise(const nlohmann::json &j)
{
    for (auto &light : j.at("Lights"))
    {
        AddLight( light.at("Color").get<glm::vec4>(),light.at("Position").get<glm::vec4>(),light.at("PaddingAndRadius").get<glm::vec4>());
    }
}
void LightManager::Clear()
{
    m_LightCount = 0;
    m_Lights.clear();
}
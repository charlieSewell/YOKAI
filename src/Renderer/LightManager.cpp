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
PointLight* LightManager::GetLight(unsigned int lightIndex)
{
    return (&m_Lights[lightIndex]);
}
void LightManager::UpdateLights()
{
    Renderer::getInstance().UpdateLights(m_Lights);
}
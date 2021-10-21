#pragma once
#include "DataTypes.hpp"
#include "Renderer/Renderer.hpp"
#include "Export.hpp"
class YOKAI_API LightManager
{
    public:
        LightManager();
        unsigned int AddLight(glm::vec4 color, glm::vec4 position, glm::vec4 paddingAndRadius);
        PointLight* GetLight(unsigned int lightIndex);
        void UpdateLights();
    private:
        std::vector<PointLight> m_Lights;
        unsigned int m_LightCount;
};

#pragma once
#include "DataTypes.hpp"
#include "Renderer/Renderer.hpp"
#include "Export.hpp"
#include <Imgui/imgui.h>
#include "Engine/JSONTypes.hpp"
class YOKAI_API LightManager
{
    public:
        LightManager();
        unsigned int AddLight(glm::vec4 color, glm::vec4 position, glm::vec4 paddingAndRadius);
        void DeleteLight(unsigned int lightIndex);
        PointLight* GetLight(unsigned int lightIndex);
        void UpdateLights();
        void RenderGUI();
        void Serialise(nlohmann::json &j);
        void Deserialise(const nlohmann::json &j);
        /**
         * @brief Clears the Lighting Manager
         */
        void Clear();
    private:
        std::vector<PointLight> m_Lights;
        unsigned int m_LightCount;
};

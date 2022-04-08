#pragma once
#include "Renderer/DataTypes.hpp"
#include "Renderer/Renderer.hpp"
#include <Imgui/imgui.h>
#include "Engine/JSONTypes.hpp"
#include "Renderer/PointLight.hpp"
class LightManager
{
    public:
        /**
         * @brief Construct a new Light Manager object
         */
        LightManager();
        /**
         * @brief Adds a Light to the scene
         * @param color 
         * @param position 
         * @param radius
         * @return unsigned int 
         */
        unsigned int AddLight(glm::vec3 position, glm::vec3 color, float radius);
        /**
         * @brief Adds a Light to the scene
         * @param light 
         * @return unsigned int 
         */
        unsigned int AddLight(PointLight light);
        /**
         * @brief Deletes a Light from the scene
         * @param lightIndex 
         */
        void DeleteLight(unsigned int _lightIndex);
        /**
         * @brief Get a light from an index
         * @param lightIndex 
         * @return PointLight* 
         */
        PointLight* GetLight(unsigned int lightIndex);
        /**
         * @brief Updates Lights
         */
        void UpdateLights();
        /**
         * @brief Renders Lighting Gui
         */
        void RenderGUI();
        /**
         * @brief Save scene lights 
         * @param j 
         */
        void Serialize(nlohmann::json &j);
        /**
         * @brief Loads scene lights
         * @param j 
         */
        void Deserialize(const nlohmann::json &j);
        /**
         * @brief Clears the Lighting Manager
         */
        void Clear();
    private:
        ///vector of scene lights
        std::vector<PointLight> m_Lights;
        ///light count
        unsigned int m_LightCount;
};

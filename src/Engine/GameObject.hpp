#pragma once

#include "Components/Component.hpp"
#include "Export.hpp"
#include <vector>
#include <memory>
#include <string>
#include <imgui/imgui.h>
#include <nlohmann/json.hpp>
/**
 * @Class GameObject
 * @brief Generic game object type that holds components
 */
class YOKAI_API GameObject
{
    public:
        /**
         * @brief Construct a new Game Object object
         * @param id 
         */
        GameObject(unsigned int id);
        /**
         * @brief Construct a new Game Object object
         * @param id 
         * @param objectName 
         */
        GameObject(unsigned int id, std::string objectName);
        /**
         * @brief Sets a game objects state to active
         */
        void Awake();
        /**
         * @brief Is called once on game object initialisation
         */
        void Start();
        /**
         * @brief Update Before Physics Simulation
         * @param timeDelta 
         */
        void Update(float timeDelta);
        /**
         * @brief Update After Physics Simulation
         * @param timeDelta 
         */
        void LateUpdate(float timeDelta);
        
        void Serialise(nlohmann::json &data);
        
        void Deserialise(const nlohmann::json &data);
        /**
         * @brief Draws the game Object
         */
        void Draw();
        /**
         * @brief Gets the Object ID
         * @return unsigned int 
         */
        unsigned int GetObjectID();
        /**
         * @brief Set the Objects Name
         * @param objectName 
         */
        void SetName(std::string objectName);
        /**
         * @brief Get the Objects Name
         * @return std::string 
         */
        std::string GetName(){return m_objectName;}
        /**
         * @brief Renders the components GUI
         */
        void RenderGUI();
    private:
        ///Game object ID
        unsigned int m_gameObjectID;
        std::string m_objectName = "Default Object";
        ///Vector of game object Components
        std::vector<std::shared_ptr<Component>> m_components;
    public:
        /**
         * @brief Adds A component to the game object
         * @tparam T 
         * @return std::shared_ptr<T> 
         */
        template <typename T> std::shared_ptr<T> AddComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
            // Check that we don't already have a component of this type.
            for (auto& exisitingComponent : m_components)
            {
                if (std::dynamic_pointer_cast<T>(exisitingComponent))
                {
                    return std::dynamic_pointer_cast<T>(exisitingComponent); // 2
                }
            }
            std::shared_ptr<T> newComponent = std::make_shared<T>(this); 
            newComponent->Awake();
            m_components.push_back(newComponent);
            
            return newComponent;
        };
        /**
         * @brief Gets a component from the game object
         * @tparam T 
         * @return std::shared_ptr<T> 
         */
        template <typename T> std::shared_ptr<T> GetComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            for (auto& exisitingComponent : m_components)
            {
                if (std::dynamic_pointer_cast<T>(exisitingComponent))
                {
                    return std::dynamic_pointer_cast<T>(exisitingComponent);
                }
            }
            return nullptr;
        };
};
#pragma once
#include <iostream>
#include "Model/Component.hpp"
#include <vector>
#include <memory>
class GameObject
{
    public:
        void Awake();
        void Start();
        void Update(float timeDelta);
        void Draw();
    private:
        std::vector<std::shared_ptr<Component>> m_components;
    public:
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
            m_components.push_back(newComponent);
            
            return newComponent;
        };
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
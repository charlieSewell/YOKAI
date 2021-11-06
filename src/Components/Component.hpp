#pragma once
#include <nlohmann/json.hpp>
class GameObject;
/**
 * @class Component
 * @brief Inherited type of all components
 */
class Component
{
    public:
        /**
         * @brief Construct a new Component object
         * @param parent 
         */
        Component(GameObject* parent) : m_parent(parent){}
        /**
         * @brief Runs when component is added to gameobject
         */
        virtual void Awake() {}
        /**
         * @brief Runs once when the scene is ready to go
         */
        virtual void Start() {}
        /**
         * @brief Updates Before Physics Simulation
         * @param deltaTime 
         */
        virtual void Update(float deltaTime) {}
        /**
         * @brief Updates After Physics Simulation
         * @param deltaTime 
         */
        virtual void LateUpdate(float deltaTime) {}
        /**
         * @brief Draws once a frame after update
         */
        virtual void Draw() {}
        /**
         * @brief Renders Component GUI
         */
        virtual void RenderGUI() {}
        /**
         * @brief Serialises this component
         * @param j jsonstream
         */
        virtual void Serialize(nlohmann::json &j) {}
        /**
         * @brief Deserialises this component
         * @param j jsonstream
         */
        virtual void Deserialize(const nlohmann::json &j) {}
    protected:
        ///parent game object
        std::string m_type;
        GameObject* m_parent;
		bool m_hasStarted = false;
};
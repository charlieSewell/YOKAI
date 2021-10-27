#pragma once

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
    protected:
        ///parent game object
        GameObject* m_parent;
		bool m_hasStarted = false;
};
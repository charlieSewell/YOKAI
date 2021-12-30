#pragma once

#include "Model/ModelManager.hpp"
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include "Engine/Yokai.hpp"
#include "Model/Animator.hpp"
/**
 * @class DrawableEntity
 * @brief Draws a model to the screen
 */
class DrawableEntity : public Component {
    public: 
        /**
         * @brief Construct a new Drawable Entity object
         * @param parent 
         */
        DrawableEntity(GameObject* parent);
        /**
         * @brief Runs once when scene is ready to go
         */
        void Start();
        /**
         * @brief Updates once a frame before draw
         * @param deltaTime 
         */
        void Update(float deltaTime);
        /**
         * @brief Draws Model to screen
         */
        void Draw();
        /**
         * @brief Loads model from given Path
         * @param filename 
         */
        unsigned int LoadModel(std::string filename);
        /**
         * @brief Sets the Animation to be played
         * @param animation 
         */
        void SetAnimation(std::string animation);
        /**
         * @brief Get the Model ID
         * @return unsigned int 
         */
        unsigned int GetModelID(){return m_modelID;}
        /**
         * @brief Set the Model ID
         * @param modelID 
         */
		void SetModelID(unsigned int modelID);
        /**
         * @brief Render object GUI
         */
        void RenderGUI();
        /**
         * @brief Set the Offset fron transform
         * @param offset 
         */
        void SetOffset(glm::mat4 offset);
        /**
         * @brief Get the Offset from the transform
         * @return glm::mat4 
         */
        glm::mat4 GetOffset();

    private:
        ///Model ID
        unsigned int m_modelID;
        ///Animator of model
        Animator* m_animator = nullptr;
        ///Offset from transform
        glm::mat4 m_offset;
};

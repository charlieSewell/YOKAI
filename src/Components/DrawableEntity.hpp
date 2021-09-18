#pragma once

#include "Engine/ModelManager.hpp"
#include "Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Component.hpp"
#include "Export.hpp"
#include "Engine/Yokai.hpp"
/**
 * @class DrawableEntity
 * @brief Draws a model to the screen
 */
class YOKAI_API DrawableEntity : public Component {
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
        void LoadModel(std::string filename);
        /**
         * @brief Get the Model ID
         * @return unsigned int 
         */
        unsigned int GetModelID(){return modelID;}
    private:
        ///Model ID
        unsigned int modelID;
};

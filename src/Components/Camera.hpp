//Camera.hpp
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.hpp"
#include "Engine/GameObject.hpp"
#include "Export.hpp"
#include "Transform.hpp"

/**
 * @class Camera
 * @brief Camera component to attach to game object
 */
class YOKAI_API Camera : public Component
{
    public:
        /**
         * @brief Constructor for camera
         */
        Camera(GameObject* parent);

        void Update(float deltaTime) override;
        /**
         * @brief Returns The view Matrix of the Camera
         * @return mat4
         */

        glm::mat4 getViewMatrix();
        /**
         * @brief Registers the View Matrix with the EMS
         */
        void registerViewMatrix();
        /**
         * @brief Registers the Projection matrix with the EMS
         */
        void registerPerspective();
        ///position of the camera
	    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        ///front direction of the camera
        glm::vec3 m_frontDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        ///up direction of the camera
        glm::vec3 m_upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
        ///perspective of the camera
        glm::mat4 m_perspective = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 1.0f, 300.0f);
};

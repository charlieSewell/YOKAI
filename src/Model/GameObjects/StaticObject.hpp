#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Controller/ModelManager.hpp"
#include "GameObject.hpp"
#include "Model/Components/PhysicsComponent.hpp"
#include "View/Renderer/Shader.hpp"

/**
 * @class StaticObject
 * @brief Child of GameObject for all static objects within the game. Inherits physics component.
 */
class StaticObject : public GameObject
{
  public:
    /*!
     * @brief Constructor
     * @param string - modelName
     */
    StaticObject(const std::string& modelName);
    /**
     * @brief Destructor for static object
     */
    ~StaticObject();
    /**
     * @brief Sets the collider
     * @param width
     * @param length
     * @param height
     */
    void setCollider(float width, float height, float length) override;
    /*!
     * @brief Draw call for the staticObject model
     */
    void draw() override;

  private:
    ///Physics Component
	PhysicsComponent m_physics;
    /// Stores associated model id of the staticObject
    int modelID;
};
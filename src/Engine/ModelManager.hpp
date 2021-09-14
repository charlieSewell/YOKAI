
#pragma once

#include "Model/Model.hpp"
#include "Model/ObjectLoading/ModelLoader.hpp"
#include "Engine/GameObjectManager.hpp"
#include <map>
#include <array>
#include <glm/glm.hpp>
#include "Export.hpp"
#include <memory>
#include <vector>

/**
 * @class ModelManager
 * @brief Responsible for managing models
 */
class YOKAI_API ModelManager
{
  public:

    /*!
     * @brief Constructor
     */
    ModelManager();

    /*!
     * @brief Getter for model id from the specified filename
     * @param string - filename
     * @return modelCount-1
     */
    auto GetModelID(const std::string& filename) -> size_t;

    /*!
     * @brief Getter for model with the specified id
     * @param size_t - modelID
     * @return shared_ptr<Model>
     */
    std::shared_ptr<Model> GetModel(size_t modelID);

    /*!
     * @brief Calls the draw function for the specified model
     * @param size_t - id
     * @param mat4 - transform
     */
    void DrawModel(size_t id, glm::mat4 transform);
    void DrawModel(size_t id, glm::mat4 transform, std::vector<glm::mat4> &finalTransforms);

  private:
    /// Model loader
    ModelLoader modelLoader;

    /// Number of models
    size_t modelCount = 0;

    /// Map of models and model id's
    std::map<std::string,size_t>modelIDtoName;

    /// Vector of models
    std::vector<Model> models;

    /// Shader pointer
    Shader *modelShader;
};

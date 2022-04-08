#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "Engine/Component.hpp"
/**
 * @class Transform
 * @brief Class that encapsulates glm mat4
 */
class Transform : public Component
{
public:

	//ctrs
	Transform(GameObject* parent);
	Transform();
	Transform(glm::mat4 matrix);
	
	void Translate(glm::vec3 translation);
	/**
	 * @brief Translates the transform on a x,y,z coordinate
	 * @param x
	 * @param y
	 * @param z
	 */
	void Translate(float x, float y, float z);
	/**
	 * @brief Translates post multiply on a vector
	 * @param translation
	 */
	void TranslatePostMultiply(glm::vec3 translation);
    /**
     * @brief Translates post multiply on a x,y,z coordinate
     * @param translation
     */
	void TranslatePostMultiply(float x, float y, float z);
	/**
	 * @brief Rotates the transform
	 * @param angle
	 * @param upVector
	 */
	void Rotate(float Angle, glm::vec3 upVector);
	/**
	 * @brief Scales the transform given a vector
	 * @param scale
	 */
	void Scale(glm::vec3 scale);
    /**
     * @brief Scales the transform given a x,y,z coordinate
     * @param scale
     */
	void Scale(float x, float y, float z);
	/**
	 * @brief Scales the transform on a scalar
	 * @param scale
	 */
	void Scale(float scale);
    /**
     * @brief Gets the Scale
     * @return vec3
     */
	glm::vec3 GetScale();
	/**
	 * @brief Gets the rotation
	 * @return quat
	 */
	glm::quat GetRotation();
	/**
	 * @brief Gets the position
	 * @return vec3
	 */
	glm::vec3 GetPosition();
	/**
	 * @brief Gets the transform
	 * @return mat4
	 */
	glm::mat4 GetMatrix();
    /**
     * @brief Sets the scale given a vector
     * @param scale
     */
	void SetScale(glm::vec3 scale);
    /**
     * @brief Sets the scale given a x,y,z coordinate
     * @param scale
     */
	void SetScale(float x, float y, float z);
	/**
	 * @brief sets the scale given a scalar
	 * @param scale
	 */
	void SetScale(float scale);
    /**
     * @brief Sets the rotation given a quat
     * @param rotation
     */
	void SetRotation(glm::quat rotation);
    /**
     * @brief Sets the position given a vector
     * @param position
     */
	void SetPosition(glm::vec3 position);
	/**
	 * @brief Sets the position given a x,y,z coordinate
	 * @param x
	 * @param y
	 * @param z
	 */
	void SetPosition(float x, float y, float z);
    /**
     * Overloaded = operator
     * @param other
     * @return
     */
	Transform& operator=(const Transform &other);
	/**
	 * @brief Deserializes the transform
	 * @param jsonstream
	 */
	void Deserialize(const nlohmann::json &j) override;
	/**
	 * @brief Serializes the transform
	 * @param jsonstream
	 */
	void Serialize( nlohmann::json &j) override;
	/**
	 * @brief Renders the Transforms GUI
	 */
	void RenderGUI() override;
private:
    ///transform
	glm::mat4 m_transform = {};
    ///scale
	glm::vec3 m_scale = {1.0f,1.0f,1.0f};
	///rotation
	glm::quat m_rotation = {};
	///position
	glm::vec3 m_position = {};
	///skey
	glm::vec3 m_skew = {};
	///perspective
	glm::vec4 m_perspective = {};
    /**
     * @brief Decomposes a transform into their componenets
     */
	void Decompose();
	/**
	 * @brief Recomposes components into a transform
	 */
	void Recompose();
};
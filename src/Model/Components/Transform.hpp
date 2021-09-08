#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "Model/Component.hpp"
#include "Controller/Export.hpp"
/**
 * @class Transform
 * @brief Class that encapsulates glm mat4
 */
class YOKAI_API Transform : public Component
{
public:
	Transform(GameObject* parent);
	Transform();
	
	void translate(glm::vec3 translation);
	/**
	 * @brief Translates the transform on a x,y,z coordinate
	 * @param x
	 * @param y
	 * @param z
	 */
	void translate(float x, float y, float z);
	/**
	 * @brief Translates post multiply on a vector
	 * @param translation
	 */
	void translatePostMultiply(glm::vec3 translation);
    /**
     * @brief Translates post multiply on a x,y,z coordinate
     * @param translation
     */
	void translatePostMultiply(float x, float y, float z);
	/**
	 * @brief Rotates the transform
	 * @param angle
	 * @param upVector
	 */
	void rotate(float angle, glm::vec3 upVector);
	/**
	 * @brief Scales the transform given a vector
	 * @param scale
	 */
	void scale(glm::vec3 scale);
    /**
     * @brief Scales the transform given a x,y,z coordinate
     * @param scale
     */
	void scale(float x, float y, float z);
	/**
	 * @brief Scales the transform on a scalar
	 * @param scale
	 */
	void scale(float scale);
    /**
     * @brief Gets the Scale
     * @return vec3
     */
	glm::vec3 getScale();
	/**
	 * @brief Gets the rotation
	 * @return quat
	 */
	glm::quat getRotation();
	/**
	 * @brief Gets the position
	 * @return vec3
	 */
	glm::vec3 getPosition();
	/**
	 * @brief Gets the transform
	 * @return mat4
	 */
	glm::mat4 getMatrix();
    /**
     * @brief Sets the scale given a vector
     * @param scale
     */
	void setScale(glm::vec3 scale);
    /**
     * @brief Sets the scale given a x,y,z coordinate
     * @param scale
     */
	void setScale(float x, float y, float z);
	/**
	 * @brief sets the scale given a scalar
	 * @param scale
	 */
	void setScale(float scale);
    /**
     * @brief Sets the rotation given a quat
     * @param rotation
     */
	void setRotation(glm::quat rotation);
    /**
     * @brief Sets the position given a vector
     * @param position
     */
	void setPosition(glm::vec3 position);
	/**
	 * @brief Sets the position given a x,y,z coordinate
	 * @param x
	 * @param y
	 * @param z
	 */
	void setPosition(float x, float y, float z);
    /**
     * Overloaded = operator
     * @param other
     * @return
     */
	Transform& operator=(const Transform &other);

private:
    ///transform
	glm::mat4 m_transform;
    ///scale
	glm::vec3 m_scale;
	///rotation
	glm::quat m_rotation;
	///position
	glm::vec3 m_position;
	///skey
	glm::vec3 m_skew;
	///perspective
	glm::vec4 m_perspective;
    /**
     * @brief Decomposes a transform into their componenets
     */
	void decompose();
	/**
	 * @brief Recomposes components into a transform
	 */
	void recompose();
};
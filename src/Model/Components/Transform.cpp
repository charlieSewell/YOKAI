#include "Transform.hpp"

Transform::Transform()
	: m_transform(glm::mat4(1.0f))
{
	decompose();
}

Transform::Transform(glm::vec3 scale, glm::quat rotation, glm::vec3 position)
	: m_transform(glm::mat4(1.0f)), m_scale(scale), m_rotation(rotation), m_position(position)
{
	recompose();
	decompose();
}

Transform::Transform(const Transform &other)
{
	m_transform = other.m_transform;
	decompose();
}

Transform::Transform(glm::mat4 matrix)
{
	m_transform = matrix;
	decompose();
}

void Transform::decompose()
{
	glm::decompose(m_transform, m_scale, m_rotation, m_position, m_skew, m_perspective);
}

void Transform::recompose()
{
	m_transform = glm::translate(m_position) * glm::mat4_cast(m_rotation) * glm::scale(m_scale);
}

void Transform::translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation);
}

void Transform::translate(float x, float y, float z)
{
	m_transform = glm::translate(m_transform, glm::vec3(x, y, z));
}

void Transform::translatePostMultiply(glm::vec3 translation)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), translation);
	m_transform = translationMatrix * m_transform;
}

void Transform::translatePostMultiply(float x, float y, float z)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
	m_transform = translationMatrix * m_transform;
}

void Transform::rotate(float angle, glm::vec3 upVector)
{
	m_transform = glm::rotate(m_transform, angle, upVector);
}

void Transform::scale(glm::vec3 scale)
{
	m_transform = glm::scale(m_transform, scale);
}

void Transform::scale(float x, float y, float z)
{
	m_transform = glm::scale(m_transform, glm::vec3(x, y, z));
}

void Transform::scale(float scale)
{
	m_transform = glm::scale(m_transform, glm::vec3(scale, scale, scale));
}

glm::vec3 Transform::getScale()
{
	decompose();
	return(m_scale);
}

glm::quat Transform::getRotation()
{
	decompose();
	return(m_rotation);
}

glm::vec3 Transform::getPosition()
{
	return(m_transform[3]);
}

glm::mat4 Transform::getMatrix()
{
	return m_transform;
}

void Transform::setScale(glm::vec3 scale)
{
	decompose();
	m_scale = scale;
	recompose();
}

void Transform::setScale(float x, float y, float z)
{
	decompose();
	m_scale = glm::vec3(x, y, z);
	recompose();
}

void Transform::setScale(float scale)
{
	decompose();
	m_scale = glm::vec3(scale, scale, scale);
	recompose();
}

void Transform::setRotation(glm::quat rotation)
{
	decompose();
	m_rotation = rotation;
	recompose();
}

void Transform::setPosition(glm::vec3 position)
{
	decompose();
	m_position = position;
	recompose();
}

void Transform::setPosition(float x, float y, float z)
{
	decompose();
	m_position = glm::vec3(x, y, z);
	recompose();
}

Transform& Transform::operator=(const Transform& other)
{
	m_transform = other.m_transform;
	return *this;
}

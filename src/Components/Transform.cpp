#include "Transform.hpp"
#include "imgui/imgui.h"
#include "ImGuizmo.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
Transform::Transform(GameObject* parent)
	: Component(parent), m_transform(glm::mat4(1.0))
{

}

Transform::Transform()
	: Component(nullptr), m_transform(glm::mat4(1.0))
{

}

Transform::Transform(glm::mat4 matrix)
	: Component(nullptr), m_transform(matrix)
{
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
	m_rotation = glm::conjugate(m_rotation);
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
void Transform::RenderGUI()
{
	float position[3];
	float rotation[3];
	float scale[3];
	if(ImGui::TreeNode("Transform"))
	{
		ImGuizmo::DecomposeMatrixToComponents(&m_transform[0][0],&position[0],&rotation[0],&scale[0]);
		ImGui::DragFloat3("Position: ",&position[0],0.1f);
		ImGui::DragFloat3("Rotation: ",&rotation[0],0.1f);
		ImGui::DragFloat3("Scale: ",&scale[0],0.1f);
		ImGui::TreePop();
        ImGui::Separator();
		ImGuizmo::RecomposeMatrixFromComponents(&position[0],&rotation[0],&scale[0],&m_transform[0][0]);
	}
}
void Transform::Deserialize(const nlohmann::json &j)
{
	for(auto& component : j.at("Components"))
	{
		if(component.at("Type").get<std::string>() == "Transform")
		{
			std::vector<float> temp = component.at("matrix").get<std::vector<float>>();
			glm::mat4 tempMat = glm::make_mat4(&temp[0]);
			m_transform = tempMat;
			decompose();
		}
	}	
}
void Transform::Serialise(nlohmann::json &j)
{
	nlohmann::json temp = nlohmann::json::object();
	std::vector<float> flatMat;
	flatMat.push_back(m_transform[0][0]);
    flatMat.push_back(m_transform[0][1]);
    flatMat.push_back(m_transform[0][2]);
    flatMat.push_back(m_transform[0][3]);

    flatMat.push_back(m_transform[1][0]);
    flatMat.push_back(m_transform[1][1]);
    flatMat.push_back(m_transform[1][2]);
    flatMat.push_back(m_transform[1][3]);

    flatMat.push_back(m_transform[2][0]);
    flatMat.push_back(m_transform[2][1]);
    flatMat.push_back(m_transform[2][2]);
    flatMat.push_back(m_transform[2][3]);

    flatMat.push_back(m_transform[3][0]);
    flatMat.push_back(m_transform[3][1]);
    flatMat.push_back(m_transform[3][2]);
    flatMat.push_back(m_transform[3][3]);

	temp["Type"] = "Transform";
	temp["matrix"] = flatMat;
	j.push_back(temp);
}
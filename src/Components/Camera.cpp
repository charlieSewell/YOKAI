#include "Camera.hpp"
#include <glm/gtx/string_cast.hpp>
#include "Engine/EventManager.hpp"
#include <iostream>
Camera::Camera(GameObject* parent)
	: Component(parent)
{
    registerViewMatrix();
    registerPerspective();
}

void Camera::Update(float deltaTime)
{
    //glm::vec3 temp = m_parent->GetComponent<Transform>()->getPosition();
}


glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_frontDirection, m_upDirection);
}

void Camera::registerViewMatrix()
{
    auto viewMatrix = [&]()
    {
      return glm::lookAt(m_position, m_position + m_frontDirection, m_upDirection);
    };

    EMS::getInstance().add(ReturnMat4Event::getViewMatrix, viewMatrix);
}
void Camera::registerPerspective()
{
    auto perspective = [&]()
    {
        return m_perspective;
    };

    EMS::getInstance().add(ReturnMat4Event::getPerspective, perspective);
}
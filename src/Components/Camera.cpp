#include "Camera.hpp"
#include <glm/gtx/string_cast.hpp>
#include "Engine/EventManager.hpp"
#include <iostream>
Camera::Camera(GameObject* parent)
	: Component(parent)
{
}
void Camera::Awake()
{
    if(m_parent->GetComponent<Transform>() == nullptr)
    {
        m_transform = m_parent->AddComponent<Transform>();
    }
    registerViewMatrix();
    registerPerspective();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(getPosition(), getPosition() + m_frontDirection, m_upDirection);
}

void Camera::registerViewMatrix()
{
    auto viewMatrix = [&]()
    {
		return glm::lookAt(getPosition(), getPosition() + m_frontDirection, m_upDirection);
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
glm::vec3 Camera::getPosition()
{
   return m_parent->GetComponent<Transform>()->getPosition() + m_posOffset;
}
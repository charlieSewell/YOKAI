#include "Camera.hpp"

#include "Controller/EventManager.hpp"

Camera::Camera(GameObject* parent)
	: Component(parent)
{
    registerViewMatrix();
    registerPerspective();
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
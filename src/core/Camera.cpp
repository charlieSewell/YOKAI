#include "Camera.hpp"
#include "Engine/EventManager.hpp"

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
    RegisterViewMatrix();
    RegisterPerspective();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(GetPosition(), GetPosition() + m_frontDirection, m_upDirection);
}

void Camera::RegisterViewMatrix()
{
    auto viewMatrix = [&]()
    {
		return glm::lookAt(GetPosition(), GetPosition() + m_frontDirection, m_upDirection);
    };

    EMS::getInstance().add(ReturnMat4Event::getViewMatrix, viewMatrix);
}
void Camera::RegisterPerspective()
{
    auto perspective = [&]()
    {
        return m_perspective;
    };

    EMS::getInstance().add(ReturnMat4Event::getPerspective, perspective);
}
glm::vec3 Camera::GetPosition()
{
   return m_parent->GetComponent<Transform>()->GetPosition() + m_posOffset;
}
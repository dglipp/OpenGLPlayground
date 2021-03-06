#include <INTERNAL/Camera.h>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera()
    : m_Position(0.0f, 0.0f, 0.0f), m_Direction(0.0f, 0.0f, -1.0f), m_UpDirection(0.0f, 1.0f, 0.0f)
{
    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDirection);
}
        
Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUpDirection)
    : m_Position(position), m_Direction(direction), m_UpDirection(worldUpDirection)
{
    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDirection);
}
        
Camera::~Camera()
{
}

void Camera::setDirectionOffset(float x, float y)
{
    m_Direction.x = cos(glm::radians(x)) * cos(glm::radians(y));
    m_Direction.y = sin(glm::radians(y));
    m_Direction.z = sin(glm::radians(x)) * cos(glm::radians(y));
    m_Direction = glm::normalize(m_Direction);
    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDirection);
}

void Camera::rotateDirection(float x, float y)
{
    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, glm::radians(x), glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(y), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Direction += glm::vec3(rotation * glm::vec4(m_Direction, 1.0f));
    m_Direction = glm::normalize(m_Direction);
    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDirection);
}

void Camera::move(float longitudinal, float transverse)
{
    m_Position += longitudinal * m_Direction + transverse * glm::normalize(glm::cross(m_Direction, m_UpDirection));
    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDirection);
}
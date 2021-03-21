#pragma once

#include <VENDOR/GLM/glm.hpp>

class Camera
{
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUpDirection = glm::vec3(0.0f, 1.0f, 0.0f));
        ~Camera();

        glm::mat4 & getView() { return m_View; }
        void setDirectionOffset(float x, float y);
        void rotateDirection(float x, float y);
        void move(float longitudinal, float transverse);

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Direction;
        glm::vec3 m_UpDirection;
        glm::mat4 m_View;
};
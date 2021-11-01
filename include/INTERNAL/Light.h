#pragma once

#include <VENDOR/GLM/glm.hpp>

namespace light
{
    class Ambient
    {
        protected:
            glm::vec4 m_Ambient;
            glm::vec4 m_Diffuse;
            glm::vec4 m_Specular;

        protected:
            Ambient(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight);

        public:
            Ambient();
            Ambient(glm::vec4 ambientLight);

            glm::vec4 getAmbient();
            void setAmbient(glm::vec4 ambientLight);
    };

    class Directional : public Ambient
    {
        protected:
            glm::vec3 m_Direction;

        public:
            Directional();
            Directional(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight, glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f));

            glm::vec4 getDiffuse();
            glm::vec4 getSpecular();
            glm::vec3 getDirection();

            void setDiffuse(glm::vec4 diffuseLight);
            void setSpecular(glm::vec4 specularLight);
            void setDirection(glm::vec3 direction);
    };

    class Positional : public Ambient
    {
    };
}
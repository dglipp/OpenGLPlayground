#pragma once

#include <VENDOR/GLM/glm.hpp>
namespace mtl
{
    class BaseMtl
    {
        protected:
            glm::vec4 m_Ambient;
            glm::vec4 m_Diffuse;
            glm::vec4 m_Specular;
            float m_Shininess;

        public:
            BaseMtl();
            BaseMtl(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess);

            glm::vec4 getAmbient();
            glm::vec4 getDiffuse();
            glm::vec4 getSpecular();
            float getShininess();

            void setAmbient(glm::vec4 ambient);
            void setDiffuse(glm::vec4 diffuse);
            void setSpecular(glm::vec4 specular);
            void setShininess(float shininess);
    };
}
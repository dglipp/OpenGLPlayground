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
        protected:
            glm::vec3 m_Location;
            float m_Kc;
            float m_Kl;
            float m_Kq;

        public:
            Positional();
            Positional(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight,
                       glm::vec3 location = glm::vec3(0.0f, 0.0f, 0.0f),
                       float Kc = 1.2f, float Kl = 0.2f, float Kq = 0.0f);

            glm::vec4 getDiffuse();
            glm::vec4 getSpecular();
            glm::vec3 getLocation();
            float getKc();
            float getKl();
            float getKq();

            void setDiffuse(glm::vec4 diffuseLight);
            void setSpecular(glm::vec4 specularLight);
            void setLocation(glm::vec3 direction);
            void setKc(float Kc);
            void setKl(float Kl);
            void setKq(float Kq);

            float getDistanceAttenuation(glm::vec3 targetPosition);
    };

    class Spotlight : public Positional, public Directional
    {
        protected:
            float m_Cutoff;
            float m_Exponent;

        public:
            Spotlight();
            Spotlight(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight,
                      glm::vec3 location = glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f),
                      float Kc = 1.2f, float Kl = 0.2f, float Kq = 0.0f, float cutoff = 20.0f, float exponent = 10.0f);

            float getCutoff();
            float getExponent();

            void setCutoff(float cutoff);
            void setExponent(float exponent);

            float getSpotlightAttenuation(glm::vec3 targetPosition);
    };
}
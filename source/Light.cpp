#include <INTERNAL/Light.h>

#include <VENDOR/GLM/gtx/vector_angle.hpp>
namespace light
{
    Ambient::Ambient()
        : m_Ambient(0.2f, 0.2f, 0.2f, 1.0f)
    {}

    Ambient::Ambient(glm::vec4 ambientLight)
        : m_Ambient(ambientLight)
    {}

    Ambient::Ambient(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight)
        : m_Ambient(ambientLight)
        , m_Diffuse(diffuseLight)
        , m_Specular(specularLight)
    {}

    glm::vec4 Ambient::getAmbient()
    {
        return m_Ambient;
    }

    void Ambient::setAmbient(glm::vec4 ambientLight)
    {
        m_Ambient = ambientLight;
    }

    Directional::Directional()
        : Ambient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , m_Direction(0.0f, 0.0f, -1.0f)
    {}

    Directional::Directional(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight, glm::vec3 direction)
        : Ambient(ambientLight, diffuseLight, specularLight)
        , m_Direction(direction)
    {}

    glm::vec4 Directional::getDiffuse()
    {
        return m_Diffuse;
    }

    glm::vec4 Directional::getSpecular()
    {
        return m_Specular;
    }

    glm::vec3 Directional::getDirection()
    {
        return m_Direction;
    }

    void Directional::setDiffuse(glm::vec4 diffuseLight)
    {
        m_Diffuse = diffuseLight;
    }

    void Directional::setSpecular(glm::vec4 specularLight)
    {
        m_Specular = specularLight;
    }

    void Directional::setDirection(glm::vec3 direction)
    {
        m_Direction = direction;
    }

    Positional::Positional()
        : Ambient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , m_Location(0.0f, 0.0f, -1.0f)
        , m_Kc(1.2f)
        , m_Kl(0.2f)
        , m_Kq(0.0f)
    {}

    Positional::Positional(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight, glm::vec3 location,
                           float Kc, float Kl, float Kq)
        : Ambient(ambientLight, diffuseLight, specularLight)
        , m_Location(location)
        , m_Kc(Kc)
        , m_Kl(Kl)
        , m_Kq(Kq)
    {}

    glm::vec4 Positional::getDiffuse()
    {
        return m_Diffuse;
    }

    glm::vec4 Positional::getSpecular()
    {
        return m_Specular;
    }

    glm::vec3 Positional::getLocation()
    {
        return m_Location;
    }

    float Positional::getKc()
    {
        return m_Kc;
    }

    float Positional::getKl()
    {
        return m_Kl;
    }

    float Positional::getKq()
    {
        return m_Kq;
    }

    void Positional::setDiffuse(glm::vec4 diffuseLight)
    {
        m_Diffuse = diffuseLight;
    }

    void Positional::setSpecular(glm::vec4 specularLight)
    {
        m_Specular = specularLight;
    }

    void Positional::setLocation(glm::vec3 location)
    {
        m_Location = location;
    }

    void Positional::setKc(float Kc)
    {
        m_Kc = Kc;
    }

    void Positional::setKl(float Kl)
    {
        m_Kl = Kl;
    }

    void Positional::setKq(float Kq)
    {
        m_Kq = Kq;
    }

    float Positional::getDistanceAttenuation(glm::vec3 targetPosition)
    {
        float d = glm::distance(m_Location, targetPosition);
        return 1.0f / (m_Kc + d * m_Kl + d * d * m_Kq);
    }

    Spotlight::Spotlight()
        : Positional()
        , Directional()
        , m_Cutoff(20.f)
        , m_Exponent(10.0f)
    {}

    Spotlight::Spotlight(glm::vec4 ambientLight, glm::vec4 diffuseLight, glm::vec4 specularLight,
                         glm::vec3 location, glm::vec3 direction,
                         float Kc, float Kl, float Kq, float cutoff, float exponent)
        : Directional(ambientLight, diffuseLight, specularLight, direction)
        , Positional(ambientLight, diffuseLight, specularLight, location, Kc, Kl, Kq)
        , m_Cutoff(cutoff)
        , m_Exponent(exponent)
    {}
    
    float Spotlight::getCutoff()
    {
        return m_Cutoff;
    }

    float Spotlight::getExponent()
    {
        return m_Exponent;
    }

    void Spotlight::setCutoff(float cutoff)
    {
        m_Cutoff = cutoff;
    }

    void Spotlight::setExponent(float exponent)
    {
        m_Exponent = exponent;
    }

    float Spotlight::getSpotlightAttenuation(glm::vec3 targetPosition)
    {
        float phi = glm::angle(glm::normalize(m_Direction), glm::normalize(targetPosition));
        return phi > m_Cutoff ? 0.0f : powf(cos(phi), m_Exponent);
    }
}

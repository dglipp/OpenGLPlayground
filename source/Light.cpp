#include <INTERNAL/Light.h>

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

}

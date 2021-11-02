#include <INTERNAL/Material.h>

namespace mtl
{
    BaseMtl::BaseMtl()
        : m_Ambient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , m_Diffuse(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , m_Specular(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , m_Shininess(10.0f)
    {}

    BaseMtl::BaseMtl(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess)
        : m_Ambient(ambient)
        , m_Diffuse(diffuse)
        , m_Specular(specular)
        , m_Shininess(shininess)
    {}

    glm::vec4 BaseMtl::getAmbient()
    {
        return m_Ambient;
    }

    glm::vec4 BaseMtl::getDiffuse()
    {
        return m_Diffuse;
    }

    glm::vec4 BaseMtl::getSpecular()
    {
        return m_Specular;
    }

    float BaseMtl::getShininess()
    {
        return m_Shininess;
    }

    void BaseMtl::setAmbient(glm::vec4 ambient)
    {
        m_Ambient = ambient;
    }

    void BaseMtl::setDiffuse(glm::vec4 diffuse)
    {
        m_Diffuse = diffuse;
    }

    void BaseMtl::setSpecular(glm::vec4 specular)
    {
        m_Specular = specular;
    }

    void BaseMtl::setShininess(float shininess)
    {
        m_Shininess = shininess;
    }
}
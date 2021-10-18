#include <INTERNAL/Geometry.h>

#include <cmath>

namespace geo
{
    Surface::Surface()
    {
    }

    int Surface::getNVertices()
    {
        return m_Vertices.size();
    }

    int Surface::getNIndices()
    {
        return m_Indices.size();
    }

    std::vector<int> Surface::getIndices()
    {
        return m_Indices;
    }

    std::vector<glm::vec3> Surface::getVertices()
    {
        return m_Vertices;
    }

    std::vector<glm::vec3> Surface::getNormals()
    {
        return m_Normals;
    }

    std::vector<glm::vec3> Surface::getTexCoords()
    {
        return m_TexCoords;
    }

    Sphere::Sphere()
        : m_Precision(48)
    {
        init();
    }
    
    Sphere::Sphere(float precision)
        : m_Precision(precision)
    {
        init();
    }

    float Sphere::degreesToRad(float degrees)
    {
        return degrees * 2.0f * M_PI / 360.0f;
    }

    float Sphere::radToDegrees(float rads)
    {
        return rads * 360.0f / 2.0f / M_PI;
    }

    void Sphere::init()
    {
        // TODO: Create Sphere here
    }
}
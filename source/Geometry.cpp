#include <INTERNAL/Geometry.h>

#include <cmath>
#include <iostream>

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

    std::vector<glm::vec2> Surface::getTexCoords()
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
        // Calculate vertices, normals and texture coordinates
        float x, y, z, xy;
        float nx, ny, nz;
        float s, t;

        float sectorStep = 2 * M_PI / m_Precision;
        float stackStep = M_PI / m_Precision;
        float sectorAngle, stackAngle;

        for(int i = 0; i <= m_Precision; ++i)
        {
            stackAngle = M_PI / 2 - i * stackStep;
            xy = cosf(stackAngle);
            z = sinf(stackAngle);

            for(int j = 0; j <= m_Precision; ++j)
            {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);
                m_Vertices.push_back(glm::vec3(x, y, z));
                m_Normals.push_back(glm::vec3(x, y, z));

                s = (float)j / m_Precision;
                t = (float)i / m_Precision;
                m_TexCoords.push_back(glm::vec2(s, t));
            }
        }
        
        // Calculate indices
        int k1, k2;
        for(int i = 0; i < m_Precision; ++i)
        {
            k1 = i * (m_Precision + 1);
            k2 = k1 + m_Precision + 1;

            for(int j = 0; j < m_Precision; ++j, ++k1, ++k2)
            {
                if(i != 0)
                {
                    m_Indices.push_back(k1);
                    m_Indices.push_back(k2);
                    m_Indices.push_back(k1 + 1);
                }

                if(i != (m_Precision-1))
                {
                    m_Indices.push_back(k1 + 1);
                    m_Indices.push_back(k2);
                    m_Indices.push_back(k2 + 1);
                }
            }
        }
    }
}
#include <INTERNAL/Geometry.h>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>

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

    std::vector<unsigned int> Surface::getIndices()
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

    std::vector<float> Surface::getVertexBuffer()
    {
        std::vector<float> buffer;

        for (auto &&v : m_Vertices)
        {
            buffer.push_back(v.x);
            buffer.push_back(v.y);
            buffer.push_back(v.z);
        }

        return buffer;
    }

    std::vector<float> Surface::getNormalBuffer()
    {
        std::vector<float> buffer;

        for (auto &&v : m_Normals)
        {
            buffer.push_back(v.x);
            buffer.push_back(v.y);
            buffer.push_back(v.z);
        }

        return buffer;
    }

    std::vector<float> Surface::getTextureBuffer()
    {
        std::vector<float> buffer;

        for (auto &&v : m_TexCoords)
        {
            buffer.push_back(v.s);
            buffer.push_back(v.t);
        }

        return buffer;
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

    Torus::Torus()
    {
    }
    
    Torus::Torus(float innerRadius, float outerRadius)
        : m_Precision(48)
        , m_InnerRadius(innerRadius)
        , m_OuterRadius(outerRadius)
    {
        init();
    }

    Torus::Torus(float innerRadius, float outerRadius, float precision)
        : m_Precision(precision)
        , m_InnerRadius(innerRadius)
        , m_OuterRadius(outerRadius)
    {
        init();
    }

    void Torus::init()
    {
        int nVertices = (m_Precision + 1) * (m_Precision + 1);
        int nIndices = m_Precision * m_Precision * 6;
        m_Vertices.resize(nVertices);
        m_TexCoords.resize(nVertices);
        m_Normals.resize(nVertices);
        m_Indices.resize(nIndices);

        // used to calculate normal vector
        std::vector<glm::vec3> tans(nVertices);
        std::vector<glm::vec3> bitans(nVertices);


        // build first vertex ring
        for (int i = 0; i <= m_Precision; ++i)
        {
            float amount = i * 2.0f * M_PI / m_Precision;
            glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec3 initPos(rotMat * glm::vec4(0.0f, m_OuterRadius - m_InnerRadius, 0.0f, 1.0f));
            
            m_Vertices[i] = glm::vec3(initPos + glm::vec3(m_InnerRadius, 0.0f, 0.0f));
            m_TexCoords[i] = glm::vec2(0.0f, ((float)i / (float)m_Precision));

            rotMat = glm::rotate(glm::mat4(1.0f), (float) (amount + M_PI_2), glm::vec3(0.0f, 0.0f, 1.0f));
            bitans[i] = glm::vec3(rotMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
            tans[i] = glm::vec3(0.0f, 0.0f, -1.0f);
            m_Normals[i] = glm::cross(bitans[i], tans[i]);
        }

        // rotate vertex ring around Y
        for (int ring = 1; ring <= m_Precision; ++ring)
        {
            for (int v = 0; v <= m_Precision; ++v)
            {
                float amount = (float)ring * 2 * M_PI / m_Precision;
                glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0.0f, 1.0f, 0.0f));
                m_Vertices[ring * (m_Precision + 1) + v] = glm::vec3(rotMat * glm::vec4(m_Vertices[v], 1.0f));
                m_TexCoords[ring * (m_Precision + 1) + v] = glm::vec2((float) ring / (float) m_Precision, m_TexCoords[v].t);

                rotMat = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0.0f, 1.0f, 0.0f));
                bitans[ring * (m_Precision + 1) + v] = glm::vec3(rotMat * glm::vec4(bitans[v], 1.0f));
                tans[ring * (m_Precision + 1) + v] = glm::vec3(rotMat * glm::vec4(tans[v], 1.0f));

                m_Normals[ring * (m_Precision + 1) + v] = glm::vec3(rotMat * glm::vec4(m_Normals[v], 1.0f));
            }
        }

        for (int ring = 0; ring < m_Precision; ++ring)
        {
            for (int v = 0; v < m_Precision; ++v)
            {
                m_Indices[((ring * m_Precision + v) * 2) * 3 + 0] = ring * (m_Precision + 1) + v;
                m_Indices[((ring * m_Precision + v) * 2) * 3 + 1] = (ring + 1) * (m_Precision + 1) + v;
                m_Indices[((ring * m_Precision + v) * 2) * 3 + 2] = ring * (m_Precision + 1) + v + 1;
                m_Indices[((ring * m_Precision + v) * 2 + 1) * 3 + 0] = ring * (m_Precision + 1) + v + 1;
                m_Indices[((ring * m_Precision + v) * 2 + 1) * 3 + 1] = (ring + 1) * (m_Precision + 1) + v;
                m_Indices[((ring * m_Precision + v) * 2 + 1) * 3 + 2] = (ring + 1) * (m_Precision + 1) + v + 1;
            }
        }
    }
}
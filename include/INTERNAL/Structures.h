#pragma once

#include <vector>

namespace str
{

    struct Face
    {
        struct vec3
        {
            
        }

        std::vector<vec3
    }

    class Mesh
    {
        std::vector<Vertex> m_vertices;
        std::vector<Face> m_faces;

        inline Vertex getVertex(unsigned int index)
        {
            return vertices.at(index);
        }
    }

    class Vertex
    {

    }
}
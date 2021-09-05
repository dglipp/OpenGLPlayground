#include <INTERNAL/Structures.h>

namespace str
{
    Mesh::Mesh(std::string name)
        : m_name(name)
    {
    }

    Mesh::Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<TexCoord> & texCoords, std::vector<Face> & faces)
        : m_name(name), m_verts(verts), m_norms(norms), m_texCoords(texCoords), m_faces(faces)
    {
    }

    Mesh::Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<Face> & faces)
        : m_name(name), m_verts(verts), m_norms(norms), m_faces(faces)
    {
    }

    Mesh::Mesh(std::string name, std::vector<Vertex> & verts, std::vector<TexCoord> & texCoords, std::vector<Face> & faces)
        : m_name(name), m_verts(verts), m_texCoords(texCoords), m_faces(faces)
    {
    }

    Mesh::Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Face> & faces)
        : m_name(name), m_verts(verts), m_faces(faces)
    {
    }
}
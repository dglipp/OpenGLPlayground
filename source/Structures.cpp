#include <INTERNAL/Structures.h>

namespace str
{
    Mesh::Mesh()
    {
    }

    Mesh::Mesh(std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<TexCoord> & texCoords)
        : m_verts(verts), m_norms(norms), m_texCoords(texCoords)
    {
    }

    Mesh::Mesh(std::vector<Vertex> & verts, std::vector<Normal> & norms)
        : m_verts(verts), m_norms(norms)
    {
    }

    Mesh::Mesh(std::vector<Vertex> & verts, std::vector<TexCoord> & texCoords)
        : m_verts(verts), m_texCoords(texCoords)
    {
    }

    Mesh::Mesh(std::vector<Vertex> & verts)
        : m_verts(verts)
    {
    }

    Object::Object()
        : m_Name("")
    {
    }

    Object::Object(std::string name)
        : m_Name(name)
    {
    }

    Object::Object(std::string name, std::vector<Mesh> meshes)
        : m_Name(name), m_Meshes(meshes)
    {
    }
}
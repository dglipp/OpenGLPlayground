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

    Mesh::Mesh(const Mesh & mesh)
    {
        m_name = mesh.m_name;
        m_verts = mesh.m_verts;
        m_norms = mesh.m_norms;
        m_texCoords = mesh.m_texCoords;
        m_faces = mesh.m_faces;
    }

    Mesh & Mesh::operator=(const Mesh & mesh)
    {
        m_name = mesh.m_name;
        m_verts = mesh.m_verts;
        m_norms = mesh.m_norms;
        m_texCoords = mesh.m_texCoords;
        m_faces = mesh.m_faces;

        return *this;
    }

    Mesh::Mesh(Mesh && mesh)
        : m_name(std::move(mesh.m_name))
        , m_verts(std::move(mesh.m_verts))
        , m_norms(std::move(mesh.m_norms))
        , m_texCoords(std::move(mesh.m_texCoords))
        , m_faces(std::move(mesh.m_faces))
    {
    }

    Mesh & Mesh::operator=(Mesh && mesh)
    {
        m_name = std::move(mesh.m_name);
        m_verts = std::move(mesh.m_verts);
        m_norms = std::move(mesh.m_norms);
        m_texCoords = std::move(mesh.m_texCoords);
        m_faces = std::move(mesh.m_faces);

        return *this;
    }

    void Mesh::render()
    {
        
    }
}
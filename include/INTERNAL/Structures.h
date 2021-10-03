#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace str
{
    union Vertex
    {
        Vertex(double _x, double _y, double _z, double _w = 1.0)
            : x(_x), y(_y), z(_z), w(_w)
        {
        }
        
        struct
        {
            double x;
            double y;
            double z;
            double w;
        };
        double v[4];
    };

    union Normal
    {
        Normal(double _x, double _y, double _z)
            : x(_x), y(_y), z(_z)
        {
        }

        struct
        {
            double x;
            double y;
            double z;
        };
        double vn[3];
    };

    union TexCoord
    {
        TexCoord(double _u, double _v = 1.0, double _w = 1.0)
            : u(_u), v(_v), w(_w)
        {
        }

        struct
        {
            double u;
            double v;
            double w;
        };
        double vt[3];
    };

    struct Face
    {
        Face()
            : mask()
            , vertIdx()
            , normIdx()
            , texIdx()
        {
        }

        Face(bool _mask[3],
             std::vector<unsigned int> _vertIdx,
             std::vector<unsigned int> _texIdx,
             std::vector<unsigned int> _normIdx)
            : vertIdx(_vertIdx)
            , texIdx(_texIdx)
            , normIdx(_normIdx)
        {
            std::copy(_mask, _mask + 3, mask);
        }

        bool mask[3]; // in order vertex / texture / normal
        std::vector<unsigned int> vertIdx;
        std::vector<unsigned int> texIdx;
        std::vector<unsigned int> normIdx;
    };

    class Mesh
    {
        private:
            std::string m_name;
            std::vector<Vertex> m_verts;
            std::vector<Normal> m_norms;
            std::vector<TexCoord> m_texCoords;

            std::vector<Face> m_faces;
                    
        public:
            // Constructors
            Mesh(std::string name);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<TexCoord> & texCoords, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<TexCoord> & texCoords, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Face> & faces);

            // Copy constructor and assignment
            Mesh(const Mesh &  mesh);
            Mesh & operator=(const Mesh & mesh);

            // Move constructor and assignment
            Mesh(Mesh && mesh);
            Mesh & operator=(Mesh && mesh);

            // Getters
            const std::vector<str::Face> & getFaces() const
            {
                return m_faces;
            }

            str::Face getFace(unsigned int i) const
            {
                return m_faces.size() > i ? m_faces[i] : str::Face();
            }
    };
}
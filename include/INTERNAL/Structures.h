#pragma once

#include <vector>
#include <string>

namespace str
{
    union Vertex
    {
        Vertex(double _x, double _y, double _z, double _w)
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
        bool mask[3];
        int vertIdx[3];
        int normIdx[3];
        int texIdx[3];
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
            Mesh(std::string name);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<TexCoord> & texCoords, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Normal> & norms, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<TexCoord> & texCoords, std::vector<Face> & faces);
            Mesh(std::string name, std::vector<Vertex> & verts, std::vector<Face> & faces);
    };
}
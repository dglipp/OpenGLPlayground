#pragma once

#include <string>
#include <fstream>

namespace loaders
{
    class Loader
    {
        private:
            std::fstream m_file;

        public:
            Loader(std::string path)
            {
                m_file.open(path, std::ios::in);
            }

            ~Loader()
            {
                m_file.close();
            }

            virtual Mesh loadMesh();
    };

    class ObjLoader: Loader
    {
        private:
        
        public:
            Mesh loadMesh();
    }
}
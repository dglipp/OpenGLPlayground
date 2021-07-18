#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <INTERNAL/Structures.h>

namespace loaders
{
    class Loader
    {
        protected:
            std::ifstream m_file;

        public:
            Loader(std::string path)
            {
                m_file.open(path, std::ios::in);
            }

            ~Loader()
            {
                m_file.close();
            }

            virtual str::Object loadMesh() = 0;
    };

    class ObjLoader : Loader
    {
        private:

        public:
            ObjLoader(std::string path)
                : Loader(path)
            {

            }

            str::Object loadMesh();
    };
}
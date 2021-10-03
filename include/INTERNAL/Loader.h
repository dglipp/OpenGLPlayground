#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <INTERNAL/Structures.h>

namespace loaders
{
    class Loader
    {
        /**
         * @brief Base mesh loader class
         * 
         * Contains the Mesh object in memory
         */
        protected:
            /**
             * @brief the file handler 
             * 
             */
            std::ifstream m_file;

            /**
             * @brief The mesh object
             * 
             */
            str::Mesh m_object;

        public:
            /**
             * @brief Construct a new Loader object
             * 
             * @param path The mesh path
             */
            Loader(std::string path, std::string name="")
                : m_object(name)
            {
                m_file.open(path, std::ios::in);
            }

            /**
             * @brief Destroy the Loader object
             * 
             */
            ~Loader()
            {
                m_file.close();
            }

            virtual str::Mesh loadMesh(std::string name) = 0;
    };

    class ObjLoader : Loader
    {
        private:


        public:
            /**
             * @brief See base class documentation
             */
            ObjLoader(std::string path, std::string name="")
                : Loader(path, name)
            {
            }

            /**
             * @brief Obj file loader function
             * 
             * @return Returns a Mesh object 
             */
            str::Mesh loadMesh(std::string name);
    };
}
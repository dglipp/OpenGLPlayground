#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <INTERNAL/Geometry.h>

namespace load
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
            std::string m_file;

            /**
             * @brief The mesh object
             * 
             */
            geo::Mesh m_object;

        public:
            /**
             * @brief Construct a new Loader object
             * 
             * @param path The mesh path
             */
            Loader(std::string path, std::string name="")
                : m_file(path)
            {
            }

            /**
             * @brief Destroy the Loader object
             * 
             */
            ~Loader()
            {
            }

            virtual geo::Mesh loadMesh() = 0;
    };

    class ObjLoader : Loader
    {
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
            geo::Mesh loadMesh();
    };
}
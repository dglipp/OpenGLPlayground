#include <INTERNAL/Loader.h>

#include <iostream>
#include <vector>
#include <regex>

#include <INTERNAL/Geometry.h>

#include <VENDOR/GLM/glm.hpp>

namespace load
{
    geo::Mesh ObjLoader::loadMesh(std::string name)
    {
        /*
            Scan each line of file.
            Find for each line its kind (v, vn, vt, f) and add
            to the corresponding Vector.

            If face index is relative (-1) transform to absolute. 
            Face indices are 0-based for manageability with OGL.
        */
        std::string line_str;
        std::vector<std::string> line_vec;
        std::string token;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;

        std::vector<unsigned int> vertIdx;
        std::vector<unsigned int> normIdx;
        std::vector<unsigned int> texIdx;

        while(m_file)
        {
            std::getline(m_file, line_str);

            std::istringstream ss(line_str);

            while (ss >> token)
                line_vec.push_back(token);

            if(line_vec.size() == 0)
                continue;

            if(line_vec[0] == "v")
            {
                vertices.push_back(glm::vec3(std::stof(line_vec[1]),
                                             std::stof(line_vec[2]),
                                             std::stof(line_vec[3])));
            }

            if(line_vec[0] == "vn")
            {
                normals.push_back(glm::vec3(std::stof(line_vec[1]),
                                            std::stof(line_vec[2]),
                                            std::stof(line_vec[3])));
            }

            if(line_vec[0] == "vt")
            {
                texCoords.push_back(glm::vec2(std::stof(line_vec[1]), std::stof(line_vec[2])));
            }

            if(line_vec[0] == "f")
            {   
                line_vec.erase(line_vec.begin());
                for(auto lv : line_vec)
                {
                    std::istringstream tokenizer(lv);
                    std::string token;

                    std::vector<std::string> indices;
                    while(std::getline(tokenizer, token, '/'))
                        indices.push_back(token);

                    if(indices.size() == 1)
                    {
                        int idx = std::stoi(indices[0]);
                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);
                    }

                    if(indices.size() == 2)
                    {
                        int idx = std::stoi(indices[0]);
                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);

                        idx = std::stoi(indices[1]);
                        texIdx.push_back(idx > 0 ? idx - 1 : texCoords.size() - idx);
                    }

                    if(indices.size() == 3)
                    {
                        int idx = std::stoi(indices[0]);

                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);

                        idx = std::stoi(indices[2]);
                        normIdx.push_back(idx > 0 ? idx - 1 : normals.size() - idx);

                        if(indices[1] != "")
                        {
                            idx = std::stoi(indices[1]);
                            texIdx.push_back(idx > 0 ? idx - 1 : texCoords.size() - idx);
                        }
                    }
                }
            }
            line_vec.clear();
        }

        std::cout << vertIdx.size() << "   " << texIdx.size() << "   " << normIdx.size() << '\n';
        geo::Mesh obj(vertices, normals, texCoords, vertIdx);
        return obj;
    }
}
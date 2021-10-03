#include <iostream>
#include <vector>
#include <regex>

#include <INTERNAL/Loader.h>
#include <INTERNAL/Structures.h>

namespace loaders
{
    str::Mesh ObjLoader::loadMesh(std::string name)
    {
        /*
            Scan each line of file.
            Find for each line its kind (v, vn, vt, f) and add the appropriate struct
            Vertex, Normal, TexCoord, Face (See Structures.h for definition)
            to the corresponding Vector.

            If face index is relative (-1) transform to absolute. 
            Face indices are 0-based for manageability with OGL.
        */
        std::string line_str;
        std::vector<std::string> line_vec;
        std::string token;

        std::vector<str::Vertex> vertices;
        std::vector<str::Normal> normals;
        std::vector<str::TexCoord> texCoords;
        std::vector<str::Face> faces;

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
                str::Vertex vert = line_vec.size() == 4 ? str::Vertex(std::stod(line_vec[1]),
                                                                        std::stod(line_vec[2]),
                                                                        std::stod(line_vec[3])) :
                                                            str::Vertex(std::stod(line_vec[1]),
                                                                        std::stod(line_vec[2]),
                                                                        std::stod(line_vec[3]),
                                                                        std::stod(line_vec[4]));
                vertices.push_back(vert);
            }

            if(line_vec[0] == "vn")
            {
                str::Normal norm = str::Normal(std::stod(line_vec[1]),
                                                std::stod(line_vec[2]),
                                                std::stod(line_vec[3]));
                normals.push_back(norm);
            }

            if(line_vec[0] == "vt")
            {
                if(line_vec.size() == 4)
                {
                    str::TexCoord textCoord = str::TexCoord(std::stod(line_vec[1]),
                                                        std::stod(line_vec[2]),
                                                        std::stod(line_vec[3]));
                    texCoords.push_back(textCoord);
                }

                if(line_vec.size() == 3)
                {
                    str::TexCoord textCoord = str::TexCoord(std::stod(line_vec[1]),
                                                        std::stod(line_vec[2]));
                    texCoords.push_back(textCoord);
                }

                if(line_vec.size() == 2)
                {
                    str::TexCoord textCoord = str::TexCoord(std::stod(line_vec[1]));
                    texCoords.push_back(textCoord);
                }
            }

            if(line_vec[0] == "f")
            {   
                bool mask[3];
                std::vector<unsigned int> vertIdx;
                std::vector<unsigned int> normIdx;
                std::vector<unsigned int> texIdx;

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
                        mask[0] = true;
                        mask[1] = false;
                        mask[2] = false;
                        int idx = std::stoi(indices[0]);
                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);
                    }

                    if(indices.size() == 2)
                    {
                        mask[0] = true;
                        mask[1] = true;
                        mask[2] = false;

                        int idx = std::stoi(indices[0]);
                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);

                        idx = std::stoi(indices[1]);
                        texIdx.push_back(idx > 0 ? idx - 1 : texCoords.size() - idx);
                    }

                    if(indices.size() == 3)
                    {
                        mask[0] = true;
                        mask[1] = false;
                        mask[2] = true;
                        int idx = std::stoi(indices[0]);

                        vertIdx.push_back(idx > 0 ? idx - 1 : vertices.size() - idx);

                        idx = std::stoi(indices[2]);
                        normIdx.push_back(idx > 0 ? idx - 1 : normals.size() - idx);

                        if(indices[1] != "")
                        {
                            mask[1] = true;
                            idx = std::stoi(indices[1]);
                            texIdx.push_back(idx > 0 ? idx - 1 : texCoords.size() - idx);
                        }
                    }
                }
                faces.push_back(str::Face(mask, vertIdx, texIdx, normIdx));
            }
            line_vec.clear();
        }
        str::Mesh obj(name, vertices, normals, texCoords, faces);
        return obj;
    }
}
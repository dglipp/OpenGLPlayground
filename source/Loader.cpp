#include <INTERNAL/Loader.h>
#include <INTERNAL/Structures.h>
#include <iostream>
#include <vector>

namespace loaders
{
    str::Object ObjLoader::loadMesh()
    {
        if (m_file) {
            m_file.seekg (0, m_file.end);
            unsigned int length = m_file.tellg();
            m_file.seekg (0, m_file.beg);

            char * buffer = new char [length];

            m_file.read(buffer,length);

            std::vector<str::Vertex> vertices;

            for(int i=0; i<length; i++)
            {
                if(buffer[i] == 'v')
                {
                    str::Vertex vert(0.0,0.0,0.0,1.0);
                    int j = 2;
                    int idx = 0;
                    std::string element("");

                    do
                    {
                        if(buffer[i+j] != ' ')
                            element += buffer[i+j];
                        else
                        {
                            std::cout << element.c_str() << std::endl;
                            vert.v[idx] = std::stod(element.c_str());
                            ++idx;
                            element = "";
                        }
                        ++j;
                    }while(buffer[i+j] != '\n');
                    j = 2;
                    idx = 0;
                    vertices.push_back(vert);
                }
            }
            std::cout << "suze:     ";
            std::cout << vertices.size() << std::endl;
            std::cout << "el:     ";

            std::cout << buffer << std::endl;
            delete[] buffer;
        }
        str::Object obj;
        return obj;
    }
}
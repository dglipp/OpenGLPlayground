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

        while(m_file)
        {
            std::getline(m_file, line_str);
            std::istringstream ss(line_str);
            
            while (ss >> token)
            {
                line_vec.push_back(token);
                // TODO: here add vector line parser based on first element (v, vt, vn, f)
            }
            line_vec.clear();
        }
        str::Mesh obj(name);
        return obj;
    }
}
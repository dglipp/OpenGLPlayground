#include <INTERNAL/Loader.h>
#include <string>
#include <iostream>

#include <INTERNAL/Structures.h>

int main()
{
    using namespace std::string_literals;
    try
    {
        loaders::ObjLoader loader("../res/models/cow.obj"s);
        str::Mesh mesh = loader.loadMesh("mesh1");
        for(auto face : mesh.getFaces())
        {
            std::cout << '\n';
            
            for(auto v : face.vertIdx)
                std::cout << v << "  ";
            std::cout << '\n';

            for(auto v : face.normIdx)
                std::cout << v << "  ";

            std::cout << '\n';


        }

    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
#include <INTERNAL/Loader.h>
#include <string>
#include <iostream>

int main()
{
    try
    {
    loaders::ObjLoader loader(std::string("../res/models/cube.obj"));
    loader.loadMesh();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
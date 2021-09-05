#include <INTERNAL/Loader.h>
#include <string>
#include <iostream>


int main()
{
    using namespace std::string_literals;
    try
    {
    loaders::ObjLoader loader("../res/models/cube.obj"s);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
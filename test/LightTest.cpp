#include <INTERNAL/Light.h>

#include <VENDOR/GLM/glm.hpp>

#include <iostream>

int main()
{
    light::Ambient amb(glm::vec4(0.8, 0.2, 0.1, 1.0));
    light::Directional dir(glm::vec4(0.8, 0.2, 0.1, 1.0), glm::vec4(0.8, 0.2, 0.8, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));

    std::cout << dir.getDiffuse().y << '\n';
}
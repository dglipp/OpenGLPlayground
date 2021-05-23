#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <random>
#include <iostream>
#include <math.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(void)
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(1200, 1200, "OpenGL Test Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "[GLEW ERROR]: glew not ok" << std::endl;
    }
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        
    }

    glfwTerminate();
    return 0;
}


#include <iostream>

#include <GLFW/glfw3.h>

void
error_callback(int error, const char* description)
{
   puts(description);
}

int main()
{
   glfwSetErrorCallback(error_callback);

   if(!glfwInit())
   {
      std::cout << "ERROR: GLFW failed to Initialize" << '\n';
      return -1;
   }

   std::string WindowTitle = "TEST WINDOW";
   GLFWwindow* Window = glfwCreateWindow(960, 540, WindowTitle.c_str(), NULL, NULL);

   if(Window)
   {
        std::cout << "Window Created successfully" << '\n';
        do
        {
            glfwSwapBuffers(Window);
            glfwPollEvents();

        } while (glfwWindowShouldClose(Window) != GL_TRUE);
   }

    glfwTerminate();
    return 0;
}
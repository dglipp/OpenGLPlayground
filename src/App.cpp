#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>
#include <VENDOR/IMGUI/imgui.h>
#include <VENDOR/IMGUI/imgui_impl_glfw.h>
#include <VENDOR/IMGUI/imgui_impl_opengl3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/VertexBuffer.h>
#include <INTERNAL/VertexArray.h>
#include <INTERNAL/Shader.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/Texture.h>

#include <TESTS/TestClearColor.h>
#include <TESTS/TestTriangle.h>
#include <TESTS/TestTexture.h>
#include <TESTS/TestTransforms.h>
#include <TESTS/Test3D.h>

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

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
    const char* glsl_version = "#version 330 core";
    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDisable(GL_CULL_FACE));

    Renderer renderer;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    test::Test *currentTest = nullptr;
    test::TestMenu *testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear color");
    testMenu->RegisterTest<test::TestTriangle>("Render triangle");
    testMenu->RegisterTest<test::TestTexture>("Render textures");
    testMenu->RegisterTest<test::TestTransforms>("Transformations");
    testMenu->RegisterTest<test::Test3D>("Simple 3D rendering");

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.ResetClearColor();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Test menu");
        ImGui::SetWindowFontScale(1.8);

        if (currentTest)
        {
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->onUpdate(0.0f);
            currentTest->onRender(renderer);
        }

        currentTest->onImGuiRender();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            currentTest->SetInput(GLFW_KEY_UP);

        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            currentTest->SetInput(GLFW_KEY_DOWN);

        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            currentTest->SetInput(GLFW_KEY_LEFT);

        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            currentTest->SetInput(GLFW_KEY_RIGHT);
    }

    delete currentTest;
    if(currentTest != testMenu)
        delete testMenu;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(nullptr);
    glfwTerminate();
    return 0;
}


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>

#include <TESTS/TestTriangle.h>
#include <VENDOR/IMGUI/imgui.h>

namespace test
{
    TestTriangle::TestTriangle()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer()
    {
        m_Shader = Shader("res/shaders/triangle.glsl");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        unsigned int indices[] = { 0, 1, 2};

        m_VertexArray.Bind();

        m_VertexBuffer.SetBuffer(vertices, sizeof(vertices));
        m_ElementBuffer.SetBuffer(indices, sizeof(indices));

        m_Layout.Push<float>(3, "Position");
        m_Layout.Push<float>(3, "Color");
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

    }

    TestTriangle::~TestTriangle()
    {

    }

    void TestTriangle::onUpdate(float deltaTime)
    {

    }

    void TestTriangle::onRender(const Renderer &renderer)
    {
        renderer.Draw(m_VertexArray, m_ElementBuffer, m_Shader);
    }

    void TestTriangle::onImGuiRender(GLFWwindow *window)
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0/(ImGui::GetIO().Framerate), (ImGui::GetIO().Framerate));
    }
}

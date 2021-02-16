#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Texture.h>

#include <TESTS/TestTransforms.h>

#include <VENDOR/IMGUI/imgui.h>
#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>
#include <VENDOR/GLM/gtc/type_ptr.hpp>

#include <iostream>

namespace test
{
    TestTransforms::TestTransforms()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer(), 
          m_Position(0.0, 0.0, 0.0, 1.0), m_Displacement(0.01, 0.02, 0.0, 1.0), m_Speed(1.0),
          m_Omega(1), m_Shader("../res/shaders/transform.glsl"), m_Texture("../res/textures/buba.png")
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        m_VertexArray.Bind();

        m_VertexBuffer.SetBuffer(vertices, sizeof(vertices));
        m_ElementBuffer.SetBuffer(indices, sizeof(indices));

        m_Layout.Push<float>(3, "Position");
        m_Layout.Push<float>(2, "Texture");
        m_Layout.Push<float>(3, "Color");
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

        m_Texture.Bind(0);
        m_Shader.SetUniform1i("u_Texture", 0);

        m_VertexBuffer.Unbind();
        m_VertexArray.Unbind();
    }

    TestTransforms::~TestTransforms()
    {
    }

    void TestTransforms::onUpdate(float deltaTime)
    {
    }

    void TestTransforms::onRender(const Renderer &renderer)
    {
        glm::mat4 rot2(1.0f);

        if (m_Position.x < -0.75 || m_Position.x > 0.75)
        {
            m_Displacement.x = - m_Displacement.x;
            rot2 = glm::rotate(rot2, (float) glm::radians( float (rand() % 5)), glm::vec3(0.0, 0.0, 1.0));
        }
            
        if (m_Position.y< -0.75 || m_Position.y> 0.75)
        {
            m_Displacement.y = - m_Displacement.y;
            rot2 = glm::rotate(rot2, (float) glm::radians( float (rand() % 5)), glm::vec3(0.0, 0.0, 1.0));
        }

        m_Position += m_Speed * rot2 * m_Displacement;

        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, (float) glfwGetTime() * m_Omega, glm::vec3(0.0, 0.0, 1.0));
        trans = glm::translate(trans, glm::vec3(m_Position.x, m_Position.y, 0.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        m_Shader.SetUniformMat4f("u_Transform", trans);
        renderer.Draw(m_VertexArray, m_ElementBuffer, m_Shader);
    }

    void TestTransforms::onImGuiRender(GLFWwindow *window)
    {
        ImGui::SliderFloat("Omega", &m_Omega, -50.0f, 50.0f);
        ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 10.0f);
    }
}

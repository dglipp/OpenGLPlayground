#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Texture.h>

#include <TESTS/Test3D.h>

#include <VENDOR/IMGUI/imgui.h>

#include <iostream>
#include <vector>

namespace test
{
    Test3D::Test3D()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer(), 
          m_Shader("../res/shaders/basic3D.glsl"), m_Texture("../res/textures/buba.png"),
          m_Camera(0.0f, 0.0f, -5.0f), m_Rotation(0.0f)
    {
        float vertices[] = {
            // front
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            // back
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

            // left
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

            // right
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

            // up
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,

            // down
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 6, 5, 7, 6, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
            };

        m_VertexArray.Bind();

        m_VertexBuffer.SetBuffer(vertices, sizeof(vertices));
        m_ElementBuffer.SetBuffer(indices, sizeof(indices));

        m_Layout.Push<float>(3, "Position");
        m_Layout.Push<float>(3, "Color");
        m_Layout.Push<float>(2, "Texture");
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

        m_Texture.Bind(0);
        m_Shader.SetUniform1i("u_Texture", 0);

        m_VertexBuffer.Unbind();
        m_VertexArray.Unbind();
    }

    Test3D::~Test3D()
    {
    }

    void Test3D::onUpdate(float deltaTime)
    {
    }

    void Test3D::onRender(const Renderer &renderer)
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 90), glm::normalize(glm::vec3(0.3f, 0.1f, 0.6f)));
        m_Shader.SetUniformMat4f("u_Model", model);

        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, m_Camera.z));
        view = glm::rotate(view, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        m_Shader.SetUniformMat4f("u_View", view);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        m_Shader.SetUniformMat4f("u_Projection", projection);

        renderer.Draw(m_VertexArray, m_ElementBuffer, m_Shader);

        for ( auto input : m_Inputs)
        {
            switch(input)
            {
                case GLFW_KEY_UP:
                    m_Camera.z += 0.1;
                    break;
                case GLFW_KEY_DOWN:
                    m_Camera.z -= 0.1;
                    break;
                case GLFW_KEY_LEFT:
                    m_Rotation -= 5.0f;
                    break;
                case GLFW_KEY_RIGHT:
                    m_Rotation += 5.0f;
                    break;
            }
                
        }
        m_Inputs.clear();

    }

    void Test3D::onImGuiRender()
    {
    }
}

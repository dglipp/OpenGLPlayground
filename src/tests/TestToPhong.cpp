#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Texture.h>

#include <TESTS/TestToPhong.h>

#include <VENDOR/IMGUI/imgui.h>

#include <iostream>
#include <vector>

namespace test
{

    TestToPhong::TestToPhong()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer(), 
          m_LightShader("../res/shaders/phongLight.glsl"),
          m_ObjectShader("../res/shaders/phongObject.glsl"),
          m_Camera(glm::vec3(0.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0f))
    {

        float vertices[] = {
            // front
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            // back
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            // left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

            // right
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            // up
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

            // down
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
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
        m_Layout.Push<float>(3, "Normal");
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

        m_VertexBuffer.Unbind();
        m_VertexArray.Unbind();
    }

    TestToPhong::~TestToPhong()
    {
    }

    void TestToPhong::onUpdate(float deltatime) {}

    void TestToPhong::setMouseOption(GLFWwindow *window) {}

    void TestToPhong::onRender(const Renderer &renderer)
    {
        m_Deltatime = glfwGetTime() - m_Deltatime;
        float speed = 0.005f * m_Deltatime;

        // LIGHT RENDERING
        m_LightShader.SetUniform3f("u_LightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 view(1.0f);
        view = m_Camera.getView();
        m_LightShader.SetUniformMat4f("u_View", view);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        m_LightShader.SetUniformMat4f("u_Projection", projection);

        glm::mat4 model(1.0f);
        unsigned int radius = 100;
        unsigned int omega = 2;
        glm::vec3 lightPosition(radius*glm::sin(omega*glfwGetTime()), radius*glm::cos(omega*glfwGetTime()), radius*glm::cos(omega*glfwGetTime()));
        model = glm::scale(model, glm::vec3(0.02, 0.02, 0.02));
        model = glm::translate(model, lightPosition);
        m_LightShader.SetUniformMat4f("u_Model", model);

        renderer.Draw(m_VertexArray, m_ElementBuffer, m_LightShader);

        // OBJECT RENDERING
        m_ObjectShader.SetUniform3f("u_LightColor", 1.0f, 1.0f, 1.0f);
        m_ObjectShader.SetUniform3f("u_ObjectColor", 1.0f, 0.0f, 0.0f);
        m_ObjectShader.SetUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);

        m_ObjectShader.SetUniformMat4f("u_View", view);

        m_ObjectShader.SetUniformMat4f("u_Projection", projection);

        glm::mat4 modelObj(1.0f);
        modelObj = glm::scale(modelObj, glm::vec3(0.5, 0.5, 0.5));
        m_ObjectShader.SetUniformMat4f("u_Model", modelObj);

        renderer.Draw(m_VertexArray, m_ElementBuffer, m_ObjectShader);

        for ( auto input : m_Inputs)
        {
            switch(input)
            {
                case GLFW_KEY_W:
                    m_Camera.move(speed, 0.0f);
                    break;
                case GLFW_KEY_S:
                    m_Camera.move(-speed, 0.0f);
                    break;
                case GLFW_KEY_A:
                    m_Camera.move(0.0f, -speed);
                    break;
                case GLFW_KEY_D:
                    m_Camera.move(0.0f, speed);
                    break;
                case GLFW_KEY_UP:
                    m_Camera.rotateDirection(0, speed*20);
                    break;
                case GLFW_KEY_DOWN:
                    m_Camera.rotateDirection(0, -speed*20);
                    break;
                case GLFW_KEY_LEFT:
                    m_Camera.rotateDirection(-speed*20, 0);
                    break;
                case GLFW_KEY_RIGHT:
                    m_Camera.rotateDirection(speed*20, 0);
                    break;
            }
        }
        m_Inputs.clear();

    }

    void TestToPhong::onImGuiRender(GLFWwindow *window)
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0/(ImGui::GetIO().Framerate),
                    (ImGui::GetIO().Framerate));
    }
}

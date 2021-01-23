#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Texture.h>

#include <TESTS/TestCamera.h>

#include <VENDOR/IMGUI/imgui.h>

#include <iostream>
#include <vector>

namespace test
{
    double offset_mouse_x = 0;
    double offset_mouse_y = 0;
    double last_x = 0;
    double last_y = 0;
    bool first = true;

    void mouse_callback(GLFWwindow *window, double x, double y)
    {
        float sensitivity = 0.01f;

        if(first)
        {
            last_x = x;
            last_y = y;
            first = false;
        }

        offset_mouse_x += (x - last_x) * sensitivity;
        offset_mouse_y += (last_y - y) * sensitivity;
        last_x = x;
        last_y = y;
        // if(offset_mouse_y > 89.f) offset_mouse_y = 89.0f;
        // if(offset_mouse_y < -89.f) offset_mouse_y = -89.0f;
    }

    TestCamera::TestCamera()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer(), 
          m_Shader("../res/shaders/basic3D.glsl"), m_Texture("../res/textures/trump.png"),
          m_Camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
          m_Rotation(0.0f), m_Diff(0.11f), m_Deltatime(0.0f)
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

    TestCamera::~TestCamera()
    {
    }

    void TestCamera::onUpdate(float deltatime) {}

    void TestCamera::setMouseOption(GLFWwindow *window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetCursorPosCallback(window, mouse_callback);
    }

    void TestCamera::onRender(const Renderer &renderer)
    {
        m_Deltatime = glfwGetTime() - m_Deltatime;
        m_Camera.setDirectionOffset(offset_mouse_x, offset_mouse_y);

        glm::mat4 view(1.0f);
        view = m_Camera.getView();
        m_Shader.SetUniformMat4f("u_View", view);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        m_Shader.SetUniformMat4f("u_Projection", projection);

        unsigned int n_Particles = 1000;
        for (int i = 0; i < n_Particles; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
            model = glm::translate(model, glm::vec3(i*cos(i*5.1/10)/10, i/10, i*sin(i*(5.1 + sin(m_Diff)*0.5)/10)/10));
            model = glm::rotate(model, glm::radians((float) glfwGetTime() * 90), glm::normalize(glm::vec3(0.3f, 0.1f, 0.6f)));
            m_Shader.SetUniformMat4f("u_Model", model);

            // thousands of draw calls yess
            renderer.Draw(m_VertexArray, m_ElementBuffer, m_Shader);
        }

        float speed = 0.005f * m_Deltatime;
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
            }
        }
        m_Inputs.clear();

    }

    void TestCamera::onImGuiRender(GLFWwindow *window)
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0/(ImGui::GetIO().Framerate), (ImGui::GetIO().Framerate));
        ImGui::Text("offset_x: %.3f", offset_mouse_x);
        ImGui::Text("offset_y: %.3f", offset_mouse_y);

    }
}

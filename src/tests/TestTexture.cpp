#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Texture.h>

#include <TESTS/TestTexture.h>
#include <VENDOR/IMGUI/imgui.h>

namespace test
{
    TestTexture::TestTexture()
        : m_VertexArray(), m_VertexBuffer(), m_ElementBuffer(), m_Slot(0),
        m_Shader("../res/shaders/texture.glsl")
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 
            2, 3, 0
        };

        m_VertexArray.Bind();

        m_VertexBuffer.SetBuffer(vertices, sizeof(vertices));
        m_ElementBuffer.SetBuffer(indices, sizeof(indices));

        m_Layout.Push<float>(3, "Position");
        m_Layout.Push<float>(2, "Texture");
        m_Layout.Push<float>(3, "Color");
        m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);
        m_Textures.push_back(std::move(Texture("../res/textures/buba.png")));
        m_Textures.push_back(std::move(Texture("../res/textures/bubaText.png")));

        m_Textures[0].Bind(0);
        m_Textures[1].Bind(1);

        m_Shader.SetUniform1i("u_Texture", m_Slot);

        m_VertexBuffer.Unbind();
        m_VertexArray.Unbind();
    }

    TestTexture::~TestTexture()
    {

    }

    void TestTexture::onUpdate(float deltaTime)
    {

    }

    void TestTexture::onRender(const Renderer &renderer)
    {
        renderer.Draw(m_VertexArray, m_ElementBuffer, m_Shader);
    }

    void TestTexture::onImGuiRender(GLFWwindow *window)
    {
        if(ImGui::Button("Change Texture"))
        {
            m_Slot = 1 - m_Slot;
            m_Shader.SetUniform1i("u_Texture", m_Slot);
        }
    }
}

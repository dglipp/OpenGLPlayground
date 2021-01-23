#pragma once

#include <TESTS/Test.h>

namespace test
{
    class TestTexture : public Test
    {
        public:
            TestTexture();
            ~TestTexture();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender(GLFWwindow *window) override;
        private:
            Shader m_Shader;
            VertexArray m_VertexArray;
            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            VertexBufferLayout m_Layout;
            std::vector<Texture>  m_Textures;
            unsigned int m_Slot;
    };
}

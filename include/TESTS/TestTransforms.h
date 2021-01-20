#pragma once

#include <TESTS/Test.h>

namespace test
{
    class TestTransforms : public Test
    {
        public:
            TestTransforms();
            ~TestTransforms();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender() override;
        private:
            Shader m_Shader;
            VertexArray m_VertexArray;
            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            VertexBufferLayout m_Layout;
            Texture m_Texture;
            glm::vec4 m_Position;
            glm::vec4 m_Displacement;
            float m_Omega;
            float m_Speed;
    };
}

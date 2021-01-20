#pragma once

#include <TESTS/Test.h>

namespace test
{
    class TestTriangle : public Test
    {
        public:
            TestTriangle();
            ~TestTriangle();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender() override;
        private:
            Shader m_Shader;
            VertexArray m_VertexArray;
            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            VertexBufferLayout m_Layout;
    };
}

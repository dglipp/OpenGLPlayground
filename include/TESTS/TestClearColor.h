#pragma once

#include <TESTS/Test.h>

namespace test
{
    class TestClearColor : public Test
    {
        public:
            TestClearColor();
            ~TestClearColor();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender(GLFWwindow *window) override;
        private:
            float m_ClearColor[4];
    };
}

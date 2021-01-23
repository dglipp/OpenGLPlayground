#pragma once

#include <TESTS/Test.h>
#include <GLFW/glfw3.h>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>
#include <VENDOR/GLM/gtc/type_ptr.hpp>

#include <INTERNAL/Camera.h>

namespace test
{

    class TestCamera : public Test
    {
        public:
            TestCamera();
            ~TestCamera();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender(GLFWwindow *window) override;
            void setMouseOption(GLFWwindow *window);
            
        private:
            Shader m_Shader;
            VertexArray m_VertexArray;
            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            VertexBufferLayout m_Layout;
            Texture m_Texture;
            Camera m_Camera;
            float m_Rotation;
            float m_Diff;
            float m_Deltatime;
    };
}
#pragma once

#include <TESTS/Test.h>
#include <GLFW/glfw3.h>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>
#include <VENDOR/GLM/gtc/type_ptr.hpp>

#include <INTERNAL/Camera.h>

namespace test
{

    class TestLight : public Test
    {
        public:
            TestLight();
            ~TestLight();

            void onUpdate(float deltaTime) override;
            void onRender(const Renderer &renderer) override;
            void onImGuiRender(GLFWwindow *window) override;
            void setMouseOption(GLFWwindow *window);
            
        private:
            Shader m_LightShader;
            Shader m_ElementShader;
            VertexArray m_VertexArray;
            VertexBuffer m_VertexBuffer;
            ElementBuffer m_ElementBuffer;
            VertexBufferLayout m_Layout;
            VertexArray m_VertexArrayLight;
            VertexBuffer m_VertexBufferLight;
            ElementBuffer m_ElementBufferLight;
            VertexBufferLayout m_LayoutLight;
            Camera m_Camera;
            float m_Deltatime;
    };
}
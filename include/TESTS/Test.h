#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <functional>
#include <string>

#include <INTERNAL/Renderer.h>

namespace test
{
    class Test
    {
        public:
            Test() {}
            virtual ~Test() {}

            virtual void onUpdate(float deltaTime) {}
            virtual void onRender() {}
            virtual void onRender(const Renderer &renderer) {}
            
            virtual void onImGuiRender(GLFWwindow *window) {}

            virtual void setMouseOption(GLFWwindow *window)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            inline void SetInput(int enumVal)
            { 
                if (std::find(m_Inputs.begin(), m_Inputs.end(), enumVal) == m_Inputs.end())
                    m_Inputs.push_back(enumVal);
            }
            std::vector<int> m_Inputs;
    };

    class TestMenu : public Test
    {
        public:
            TestMenu(Test *& currentTestPointer);

            void onImGuiRender(GLFWwindow *window) override;
            template<typename T>
            void RegisterTest(const std::string &name)
            {
                m_Tests.push_back(std::make_pair(name, [](){ return new T(); }));
            }

        private:
            Test *&m_CurrentTest;
            std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    };
}

#include <INTERNAL/Renderer.h>

#include <TESTS/TestClearColor.h>
#include <VENDOR/IMGUI/imgui.h>

namespace test
{
    TestClearColor::TestClearColor()
        : m_ClearColor { 1.0f, 1.0f, 1.0f, 1.0f }
    {

    }

    TestClearColor::~TestClearColor()
    {

    }

    void TestClearColor::onUpdate(float deltaTime)
    {

    }

    void TestClearColor::onRender(const Renderer &renderer)
    {
        renderer.SetClearColor(m_ClearColor);
    }

    void TestClearColor::onImGuiRender(GLFWwindow *window)
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}

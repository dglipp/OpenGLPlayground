#include <TESTS/Test.h>
#include <VENDOR/IMGUI/imgui.h>

namespace test
{
    TestMenu::TestMenu(Test *& currentTestPointer)
        : m_CurrentTest(currentTestPointer)
    {

    }

    void TestMenu::onImGuiRender(GLFWwindow *window)
    {
        for (auto &test : m_Tests)
        {
            if (ImGui::Button(test.first.c_str()))
                m_CurrentTest = test.second();
                m_CurrentTest->setMouseOption(window);
        }
    }

}
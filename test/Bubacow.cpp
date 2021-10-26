#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/App.h>

#include <cmath>
#include <string.h>

class FragmentInterpol : public App
{
    private:
        GLuint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer;

    public:
        void startup()
        {

        }

        void render(double time)
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
        
        void onKey(int key, int action)
        {
        }
};

MAIN(FragmentInterpol);
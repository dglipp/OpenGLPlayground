#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <string>
#include <vector>

#include <INTERNAL/App.h>
#include <INTERNAL/ShaderUtility.h>


class Fragment : public App
{
    private:
        GLuint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer;

    public:
        void startup()
        {
            static const GLfloat vertices[6][2] = 
            {
                {-0.9, -0.9},
                {0.85, -0.9},
                {-0.9, 0.85},
                {0.9, -0.85},
                {0.9, 0.9},
                {-0.85, 0.9},
            };

            glCreateVertexArrays(1, &m_VAO);

            glCreateBuffers(1, &m_Buffer);
            glNamedBufferStorage(m_Buffer, sizeof(vertices), vertices, 0);

            std::vector<ShaderInfo> shaders =
            {
                {GL_VERTEX_SHADER, "/home/dglipp/Projects/OpenGLPlayground/res/shaders/triangles.vert.glsl"}
                //{GL_FRAGMENT_SHADER, "/home/dglipp/Projects/OpenGLPlayground/res/shaders/triangles.frag.glsl"},
            };

            GlslLoader loader(shaders);
            GLuint program = loader.getProgram();

            glUseProgram(program);

            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
        }

        void render(double time)
        {
            const GLfloat color[] = {0.0f, 0.0f, 0.3f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, color);


            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
};

MAIN(Fragment);
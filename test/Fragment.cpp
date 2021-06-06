#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/App.h>

#include <cmath>
#include <string>

class Fragment : public App
{
    private:
        GLuint m_Shader;
        GLuint m_VAO;

        GLuint compileShaders()
        {
            GLuint vertexShader;
            GLuint fragmentShader;
            GLuint program;

            static const GLchar * vertSource[] = 
            {
                "#version 450 core \n"
                " \n"
                "void main() \n"
                "{ \n"
                "gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
                "} \n"
            };

            static const GLchar * fragSource[] = 
            {
                "#version 450 core \n"
                " \n"
                "out vec4 color; \n"
                "void main() \n"
                "{ \n"
                "color = vec4(0.0, 0.8, 1.0, 1.0); \n"
                "} \n"
            };

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, vertSource, NULL);
            glCompileShader(vertexShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, fragSource, NULL);
            glCompileShader(fragmentShader);

            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            return program;
        }

    public:
        void startup()
        {
            m_Shader = compileShaders();
            glCreateVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);
        }

        void render(double time)
        {
            const GLfloat color[] = {0.0f, 0.0f, 0.3f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, color);
            glUseProgram(m_Shader);
            glDrawArrays(GL_POINTS, 0, 1);
            glPointSize(400.0f);
        }


};

MAIN(Fragment);
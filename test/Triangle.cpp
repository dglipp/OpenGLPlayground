#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/App.h>

#include <cmath>
#include <string>

class Triangle : public App
{
    private:
        GLuint m_Program;
        GLuint m_VAO;

        GLuint compileShaders()
        {
            GLuint vertexShader;
            GLuint fragmentShader;
            GLuint program;

            static const GLchar * vertSource[] = 
            {
                "#version 450 core \n"
                " \n"\
                "layout (location = 0) in vec4 offset;"
                "void main() \n"
                "{ \n"
                "const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), vec4(-0.25, -0.25, 0.5, 1.0), vec4(0.25, 0.25, 0.5, 1.0)); \n"
                "gl_Position = vertices[gl_VertexID] + offset; \n"
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
            m_Program = compileShaders();
            glCreateVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);
        }

        void render(double time)
        {
            const GLfloat color[] = {0.0f, 0.0f, 0.3f, 0.0f};
            GLfloat offset[] = {(float) std::sin(time * 3) * 0.5f, (float) std::cos(time * 5) * 0.5f, 0.0f, 0.0f};  
            glClearBufferfv(GL_COLOR, 0, color);
            glUseProgram(m_Program);
            glVertexAttrib4fv(0, offset);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
};

MAIN(Triangle);
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

        GLuint compileShaders()
        {
            GLuint vertexShader;
            GLuint fragmentShader;
            GLuint program;

            static const GLchar * vertSource[] = 
            {
                "#version 450 core \n"
                "layout (location = 0) in vec4 position; \n"
                "layout (location = 1) in vec4 color; \n"
                "out vec4 vs_color; \n"
                "void main() \n"
                "{ \n"
                "gl_Position = position; \n"
                "vs_color = color; \n"
                "} \n"
            };

            static const GLchar * fragSource[] = 
            {
                "#version 450 core \n"
                "in vec4 vs_color; \n"
                "out vec4 color; \n"
                "void main() \n"
                "{ \n"
                "color = vs_color; \n"
                "} \n"
            };

            GLchar message[1024];
            GLsizei len;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, vertSource, NULL);
            glCompileShader(vertexShader);
            glGetShaderInfoLog(vertexShader, 1024, &len, message);
            if (len) std::cout << "VERTEX: " << message << std::endl;
            
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, fragSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderInfoLog(fragmentShader, 1024, &len, message);
            if (len) std::cout << "FRAGMENT: "<< message << std::endl;
            
            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glGetProgramInfoLog(program, 1024, &len, message);
            if (len) std::cout << "PROGRAM: "<< message << std::endl;
            return program;
        }

    public:
        void startup()
        {
            m_Program = compileShaders();
            glCreateVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            struct Vertex
            {
                float m_x;
                float m_y;
                float m_z;
                float m_w;

                float m_r;
                float m_g;
                float m_b;
                float m_a;
                
                Vertex(float x, float y, float z, float w, float r, float g, float b, float a)
                    : m_x(x), m_y(y), m_z(z), m_w(w), m_r(r), m_g(g), m_b(b), m_a(a)
                {}
            };

            Vertex vertices[] = {
                Vertex(-1.0, -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0),
                Vertex(1.0, -1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0),
                Vertex(0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0)
            };

            glCreateBuffers(1, &m_Buffer);
            glNamedBufferStorage(m_Buffer, sizeof(vertices), vertices, 0);

            glVertexArrayAttribBinding(m_VAO, 0, 0);
            glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
            glEnableVertexArrayAttrib(m_VAO, 0);

            glVertexArrayAttribBinding(m_VAO, 1, 0);
            glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*4);
            glEnableVertexArrayAttrib(m_VAO, 1);

            glVertexArrayVertexBuffer(m_VAO, 0, m_Buffer, 0, sizeof(float)*8);
        }

        void render(double time)
        {
            const GLfloat clearColor[] = {0.0f, 0.0f, 0.1f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, clearColor);
            glUseProgram(m_Program);
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
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <INTERNAL/App.h>

#include <cmath>
#include <string>

class FragmentInterpol : public App
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
                "layout (location = 0) in vec4 offset; \n"
                "out vec4 vs_color; \n"
                "void main() \n"
                "{ \n"
                "const vec4 vertices[3] = vec4[3](vec4(-1.0, -1.0 , 1.0, 1.0), vec4(1.0, -1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0)); \n"
                "const vec4 colors[3] = vec4[3](vec4(1.0, 0.0 , 0.0, 1.0), vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 0.0, 1.0, 1.0)); \n"
                "gl_Position = vertices[gl_VertexID] + offset; \n"
                "vs_color = colors[gl_VertexID]; \n"
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
        }

        void render(double time)
        {
            const GLfloat clearColor[] = {0.0f, 0.0f, 0.1f, 0.0f};
            GLfloat offset[] = {0.0f, 0.0f, 0.0f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, clearColor);
            glUseProgram(m_Program);
            glVertexAttrib4fv(0, offset);
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
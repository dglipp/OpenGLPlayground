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
            GLuint tessControlShader;
            GLuint tessEvalShader;
            GLuint program;

            static const GLchar * vertSource[] = 
            {
                "#version 420 core \n"
                " \n"\
                "layout (location = 0) in vec4 offset; \n"
                "layout (location = 1) in vec4 color; \n"
                "out VS_OUT \n"
                "{ \n"
                "vec4 color; \n"
                "} vs_out; \n"
                "void main() \n"
                "{ \n"
                "const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), vec4(-0.25, -0.25, 0.5, 1.0), vec4(0.25, 0.25, 0.5, 1.0)); \n"
                "gl_Position = vertices[gl_VertexID] + offset; \n"
                "vs_out.color = color; \n"
                "} \n"
            };

            static const GLchar * tessControlSource[] =
            {
                "#version 420 core \n"
                " \n"
                "layout (vertices = 3) out; \n"
                " \n"
                "void main() \n"
                "{ \n"
                "if(gl_InvocationID == 0) \n"
                "{ \n"
                "gl_TessLevelInner[0] = 5.0; \n"
                "gl_TessLevelOuter[0] = 5.0; \n"
                "gl_TessLevelOuter[1] = 5.0; \n"
                "gl_TessLevelOuter[2] = 5.0; \n"
                "} \n"
                "gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;"
                "} \n"
            };

            static const GLchar * tessEvalSource[] = 
            {
                "#version 420 core \n"
                " \n"
                "layout (triangles, equal_spacing, cw) in; \n"
                " \n"
                "void main() \n"
                "{ \n"
                "gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + gl_TessCoord.y * gl_in[1].gl_Position + gl_TessCoord.z * gl_in[2].gl_Position); \n"
                "} \n"
            };

            static const GLchar * fragSource[] = 
            {
                "#version 420 core \n"
                " \n"
                "in VS_OUT \n"
                "{ \n"
                "vec4 color; \n"
                "} fs_in; \n"
                "out vec4 color; \n"
                "void main() \n"
                "{ \n"
                "color = fs_in.color; \n"
                "} \n"
            };

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, vertSource, NULL);
            glCompileShader(vertexShader);

            tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
            glShaderSource(tessControlShader, 1, tessControlSource, NULL);
            glCompileShader(tessControlShader);

            tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
            glShaderSource(tessEvalShader, 1, tessEvalSource, NULL);
            glCompileShader(tessEvalShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, fragSource, NULL);
            glCompileShader(fragmentShader);

            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, tessControlShader);
            glAttachShader(program, tessEvalShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            glDeleteShader(vertexShader);
            glDeleteShader(tessControlShader);
            glDeleteShader(tessEvalShader);
            glDeleteShader(fragmentShader);

            return program;
        }

    public:
        void startup()
        {
            m_Program = compileShaders();
            glCreateVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        void render(double time)
        {
            const GLfloat clearColor[] = {1.0f, 1.0f, 1.0f, 0.0f};
            GLfloat color[] = {(float) std::abs(std::sin(time * 3)), (float) std::abs(std::sin(time * 5)), (float) std::abs(std::sin(time * 7)), 1.0f};
            GLfloat offset[] = {(float) std::sin(time * 3) * 0.5f, (float) std::cos(time * 5) * 0.5f, 0.0f, 0.0f};  
            glClearBufferfv(GL_COLOR, 0, clearColor);
            glUseProgram(m_Program);
            glVertexAttrib4fv(0, offset);
            glVertexAttrib4fv(1, color);
            glDrawArrays(GL_PATCHES, 0, 3);
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
};

MAIN(Triangle);
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
        float m_tessGran[4] = {3.0, 30.0, 3.0, 3.0};

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
                "layout (location = 0) in vec4 offset; \n"
                "layout (location = 1) in vec4 color; \n"
                "out vec4 vs_color; \n"
                "void main() \n"
                "{ \n"
                "const vec4 vertices[3] = vec4[3](vec4(-1.0, -1.0 , 1.0, 1.0), vec4(1.0, -1.0, 1.0, 1.0), vec4(0.0, 1.0, 1.0, 1.0)); \n"
                "gl_Position = vertices[gl_VertexID] + offset; \n"
                "vs_color = color; \n"
                "} \n"
            };

            static const GLchar * tessControlSource[] =
            {
                "#version 420 core \n"
                "layout (vertices = 3) out; \n"
                "uniform vec4 tessGran; \n"
                "in vec4 vs_color[]; \n"
                "out vec4 tcs_color[]; \n"
                "void main() \n"
                "{ \n"
                "if(gl_InvocationID == 0) \n"
                "{ \n"
                "gl_TessLevelInner[0] = tessGran[0]; \n"
                "gl_TessLevelOuter[0] = tessGran[1]; \n"
                "gl_TessLevelOuter[1] = tessGran[2]; \n"
                "gl_TessLevelOuter[2] = tessGran[3]; \n"
                "} \n"
                "tcs_color[gl_InvocationID] = vs_color[gl_InvocationID]; \n"
                "gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; \n"
                "} \n"
            };

            static const GLchar * tessEvalSource[] = 
            {
                "#version 420 core \n"
                "layout (triangles, equal_spacing, cw) in; \n"
                "uniform vec3 mover; \n"
                "in vec4 tcs_color[]; \n"
                "out vec4 tes_color; \n"
                "void main() \n"
                "{ \n"
                "gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position*mover[0] + gl_TessCoord.y * gl_in[1].gl_Position*mover[1] + gl_TessCoord.z * gl_in[2].gl_Position*mover[2]); \n"
                "tes_color = (gl_TessCoord.x * tcs_color[0] + gl_TessCoord.y * tcs_color[1] + gl_TessCoord.z * tcs_color[2]); \n"
                "} \n"
            };

            static const GLchar * fragSource[] = 
            {
                "#version 420 core \n"
                "in vec4 tes_color; \n"
                "out vec4 color; \n"
                "void main() \n"
                "{ \n"
                "color = tes_color; \n"
                "} \n"
            };

            GLchar message[1024];

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, vertSource, NULL);
            glCompileShader(vertexShader);
            glGetShaderInfoLog(vertexShader, 1024, nullptr, message);
            std::cout << "VERTEX: " << message << std::endl;

            tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
            glShaderSource(tessControlShader, 1, tessControlSource, NULL);
            glCompileShader(tessControlShader);
            glGetShaderInfoLog(tessControlShader, 1024, nullptr, message);
            std::cout << "TCS: "<< message << std::endl;

            tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
            glShaderSource(tessEvalShader, 1, tessEvalSource, NULL);
            glCompileShader(tessEvalShader);
            glGetShaderInfoLog(tessEvalShader, 1024, nullptr, message);
            std::cout << "TES: "<< message << std::endl;

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, fragSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderInfoLog(fragmentShader, 1024, nullptr, message);
            std::cout << "FRAGMENT: "<< message << std::endl;
            
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
            glGetProgramInfoLog(program, 1024, nullptr, message);
            std::cout << "PROGRAM: "<< message << std::endl;
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
            if(m_tessGran[1] == 30.0f) m_tessGran[2] = +2.0f;
            if(m_tessGran[1] == 70.0f) m_tessGran[2] = -2.0f;
            const GLfloat clearColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
            GLfloat color[] = {(float) std::abs(std::sin(time * 3)), (float) std::abs(std::sin(time * 5)), (float) std::abs(std::sin(time * 7)), 1.0f};
            GLfloat offset[] = {0.0f, 0.0f, 0.0f, 0.0f};  
            glClearBufferfv(GL_COLOR, 0, clearColor);
            glUseProgram(m_Program);
            glVertexAttrib4fv(0, offset);
            glVertexAttrib4fv(1, color);
            glUniform4f(glGetUniformLocation(m_Program, "tessGran"), m_tessGran[0], m_tessGran[1], m_tessGran[1], m_tessGran[1]);
            glUniform3f(glGetUniformLocation(m_Program, "mover"), (float) std::abs(std::sin(time/1.5))*10, (float) std::abs(std::sin(time/2.5))*10, (float) std::abs(std::sin(time/5.0))*10);
            glDrawArrays(GL_PATCHES, 0, 3);
            m_tessGran[1] += m_tessGran[2];
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
        
        void onKey(int key, int action)
        {
            if(key == 265 && action == 1) m_tessGran[0]++;
            if(key == 264 && action == 1) m_tessGran[0]--;
        }
};

MAIN(Triangle);
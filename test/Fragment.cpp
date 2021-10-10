#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <string>
#include <vector>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/type_ptr.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>

#include <INTERNAL/App.h>
#include <INTERNAL/ShaderUtility.h>

union Position
{
    Position(double _x, double _y, double _z)
        : x(_x), y(_y), z(_z)
    {
    }

    Position()
    {
    }
    
    struct
    {
        double x;
        double y;
        double z;
    };
    double v[3];
};

class Fragment : public App
{
    private:
        GLint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer;

        Position m_Camera;
        Position m_ModelPosition;


    public:
        void init()
        {
            info.title = "Opengl Playground";
            info.windowWidth = 1600;
            info.windowHeight = 1200;

            info.majorVersion = 4;
            info.minorVersion = 5;
            info.samples = 0;
            info.flags.all = 0;
            info.flags.fullscreen = 1;
            info.flags.cursor = 1;
            info.flags.debug = 1;
            info.flags.vsync = 1;
        }

        void startup()
        {
            const GLfloat vertices[] = 
            {
                -1, 1, -1, -1, -1, -1, 1, -1, -1,
                1, -1, -1, 1, 1, -1, -1, 1, -1,
                1, -1, -1, 1, -1, 1, 1, 1, -1,
                1, -1, 1, 1, 1, 1, 1, 1, -1,
                1, -1, 1, -1, -1, 1, 1, 1, 1,
                -1, -1, 1, -1, 1, 1, 1, 1, 1,
                -1, -1, 1, -1, -1, -1, -1, 1, 1,
                -1, -1, -1, -1, 1, -1, -1, 1, 1,
                -1, -1, 1, 1, -1, 1, 1, -1, -1,
                1, -1, -1, -1, -1, -1, -1, -1, 1,
                -1, 1, -1, 1, 1, -1, 1, 1, 1,
                1, 1, 1, -1, 1, 1, -1, 1, -1
            };

            std::vector<ShaderInfo> shaders =
            {
                {GL_VERTEX_SHADER, "../../res/shaders/triangles.vert.glsl"},
                {GL_FRAGMENT_SHADER, "../../res/shaders/triangles.frag.glsl"}
            };

            ShaderProgram program {shaders};
            m_Program = program.createProgram();
            glUseProgram(m_Program);
            
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            glGenBuffers(1, &m_Buffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            m_Camera = Position(0, 0, 3);
            m_ModelPosition = Position(0, 0, 0);
        }

        void render(double time)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            // glClear(GL_COLOR_BUFFER_BIT);

            GLint mvMatLoc = glGetUniformLocation(m_Program, "mvMat");
            GLint projMatLoc = glGetUniformLocation(m_Program, "projMat");

            float aspect = (float) info.windowWidth / (float) info.windowHeight;
            for(int i = 0; i < 200; i++)
            {
                time = time + i * 100;
                glm::mat4 projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);    // fov to 60 degrees

                glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Camera.x, -m_Camera.y, -m_Camera.z));
                
                glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35f * time * 10),
                                                                                cos(0.52f * time * 10),
                                                                                sin(0.70f * time * 10)));
                glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float) time, glm::vec3(0.0f, 1.0f, 0.0f));
                rotMat = glm::rotate(rotMat, 1.75f * (float) time, glm::vec3(1.0f, 0.0f, 0.0f));
                rotMat = glm::rotate(rotMat, 1.75f * (float) time, glm::vec3(0.0f, 0.0f, 1.0f));

                glm::mat4 modelMat = rotMat * translateMat * glm::scale(glm::mat4(1.0f), glm::vec3(0.001f, 0.001f, 0.001f));

                glm::mat4 mvMat = viewMat * modelMat;

                glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
                glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LEQUAL);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }
};

MAIN(Fragment);
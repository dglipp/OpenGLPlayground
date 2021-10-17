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

class MultipleObjects : public App
{
    private:
        GLint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer[2];

        glm::vec3 m_Camera;
        Position m_ModelPosition[2];


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
            const GLfloat cube[] = 
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

            const GLfloat pyramid[] =
                {
                    -1, -1, 1, 1, -1, 1, 0, 1, 0,
                    1, -1, 1, 1, -1, -1, 0, 1, 0,
                    1, -1, -1, -1, -1, -1, 0, 1, 0,
                    -1, -1, -1, -1, -1, 1, 0, 1, 0,
                    -1, -1, -1, 1, -1, 1, -1, -1, 1,
                    1, -1, 1, -1, -1, -1, 1, -1, -1
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

            glGenBuffers(2, &m_Buffer[0]);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), pyramid, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            m_Camera = glm::vec3(0, 0, 3);
        }

        void render(double time)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);

            GLint mvMatLoc = glGetUniformLocation(m_Program, "mvMat");
            GLint projMatLoc = glGetUniformLocation(m_Program, "projMat");

            float aspect = (float) info.windowWidth / (float) info.windowHeight;
            glm::mat4 projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);    // fov to 60 degrees

            glm::mat4 viewMat = glm::lookAt(m_Camera,
                                            glm::vec3(0,0,0),
                                            glm::vec3(0,1,0));
            
            // CUBE
            glm::mat4 modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1f, 0.1f));

            glm::mat4 mvMat = viewMat * modelMat;

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
            
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // PYRAMID
            modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
            modelMat = glm::translate(modelMat, glm::vec3(3, 3, 0.1));

            mvMat = viewMat * modelMat;

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        void shutdown()
        {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteProgram(m_Program);
        }

                void onKey(int key, int action)
        {
            if(action == 1 || action == 2)
            switch (key)
            {
            case GLFW_KEY_W:
                m_Camera.z -= 1;
                break;
            
            case GLFW_KEY_S:
                m_Camera.z += 1;
                break;
            
            case GLFW_KEY_A:
                m_Camera.x -= 1;
                break;

            case GLFW_KEY_D:
                m_Camera.x += 1;
                break;

            case GLFW_KEY_Q:
                m_Camera.y += 1;
                break;

            case GLFW_KEY_E:
                m_Camera.y -= 1;
                break;

            default:
                break;
            }
        }
};

MAIN(MultipleObjects);
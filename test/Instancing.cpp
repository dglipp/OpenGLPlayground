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

        glm::vec3 m_Camera;
        Position m_ModelPosition;
        glm::vec3 m_RotParams;

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
                {GL_VERTEX_SHADER, "../../res/shaders/instancing.vert.glsl"},
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

            m_Camera = glm::vec3(0, 10, -2000);
            m_ModelPosition = Position(0, 0, 0);
            m_RotParams = glm::vec3(400000, 400000, 400000);
        }

        void render(double time)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);

            m_RotParams.z += 10;
            GLint viewMatLoc = glGetUniformLocation(m_Program, "viewMatrix");
            GLint projMatLoc = glGetUniformLocation(m_Program, "projMatrix");
            GLint tfLoc = glGetUniformLocation(m_Program, "tf");
            GLint rotParamsLoc = glGetUniformLocation(m_Program, "rotParams");

            float aspect = (float) info.windowWidth / (float) info.windowHeight;
            glm::mat4 projMat = glm::perspective(1.0472f, aspect, 0.1f, 1000000.0f);    // fov to 60 degrees

            glm::mat4 viewMat = glm::lookAt(m_Camera,
                                            glm::vec3(0, 0, 0),
                                            glm::vec3(0, 1, 0));
            
            glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform1f(tfLoc, (float)time);
            glUniform3fv(rotParamsLoc, 1, glm::value_ptr(m_RotParams));

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 1e6);
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
            case GLFW_KEY_1:
                m_RotParams.x += 100;
                break;

            case GLFW_KEY_2:
                m_RotParams.x -= 100;
                break;

            case GLFW_KEY_3:
                m_RotParams.y += 100;
                break;

            case GLFW_KEY_4:
                m_RotParams.y -= 100;
                break;
            
            case GLFW_KEY_5:
                m_RotParams.z += 100;
                break;

            case GLFW_KEY_6:
                m_RotParams.z -= 100;
                break;

            case GLFW_KEY_W:
                m_Camera.z -= 100;
                break;
            
            case GLFW_KEY_S:
                m_Camera.z += 100;
                break;
            
            case GLFW_KEY_A:
                m_Camera.x -= 100;
                break;

            case GLFW_KEY_D:
                m_Camera.x += 100;
                break;

            case GLFW_KEY_Q:
                m_Camera.y += 100;
                break;

            case GLFW_KEY_E:
                m_Camera.y -= 100;
                break;

            default:
                break;
            }
        }
};

MAIN(Fragment);
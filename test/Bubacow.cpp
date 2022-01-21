#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <string>
#include <vector>
#include <stack>

#include <VENDOR/GLM/glm.hpp>
#include <VENDOR/GLM/gtc/type_ptr.hpp>
#include <VENDOR/GLM/gtc/matrix_transform.hpp>

#include <INTERNAL/App.h>
#include <INTERNAL/ShaderUtility.h>
#include <INTERNAL/Geometry.h>
#include <INTERNAL/TextureUtility.h>
#include <INTERNAL/Loader.h>

class Bubacow : public App
{
    private:
        GLint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer[4];

        glm::vec3 m_Camera;
        glm::mat4 m_ProjMatrix;

        std::stack<glm::mat4> mvStack;

        geo::Mesh m_Cow;
        Texture m_Texture;

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
            load::ObjLoader meshLoader("../../res/models/dragon.obj", "marx");
            m_Cow = meshLoader.loadMesh();

            m_Texture = Texture("../../res/textures/sand.jpg");
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_Texture.getTextureID());

            std::vector<unsigned int> ind = m_Cow.getIndices();
            std::vector<float> vert = m_Cow.getVertexBuffer();
            std::vector<float> norm = m_Cow.getNormalBuffer();
            std::vector<float> tex = m_Cow.getTextureBuffer();

            std::vector<ShaderInfo> shaders =
            {
                {GL_VERTEX_SHADER, "../../res/shaders/texture.vert.glsl"},
                {GL_FRAGMENT_SHADER, "../../res/shaders/texture.frag.glsl"}
            };

            ShaderProgram program {shaders};
            m_Program = program.createProgram();
            glUseProgram(m_Program);
            
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            glGenBuffers(4, m_Buffer);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, vert.size() * 4, &vert[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]);
            glBufferData(GL_ARRAY_BUFFER, tex.size() * 4, &tex[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[2]);
            glBufferData(GL_ARRAY_BUFFER, tex.size() * 4, &tex[0], GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer[3]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);

            m_Camera = glm::vec3(0, 10, 30);

            float aspect = (float) info.windowWidth / (float) info.windowHeight;
            m_ProjMatrix = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);    // fov to 60 degrees
            GLint projMatLoc = glGetUniformLocation(m_Program, "projMat");
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix));

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LEQUAL);
        }

        void render(double time)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);

            GLint mvMatLoc = glGetUniformLocation(m_Program, "mvMat");

            glm::mat4 viewMat = glm::lookAt(m_Camera,
                                            glm::vec3(0,0,0),
                                            glm::vec3(0,1,0));
            
            mvStack.push(viewMat);

            // COW
            mvStack.push(mvStack.top());
            mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            mvStack.push(mvStack.top());
            mvStack.top() *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

            glDrawElements(GL_TRIANGLES, m_Cow.getNIndices(), GL_UNSIGNED_INT, nullptr);
            mvStack.pop();

            while(!mvStack.empty())
            {
                mvStack.pop();
            }
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

        virtual void onResize(int w, int h)
        {
            info.windowWidth = w;
            info.windowHeight = h;

            glViewport(0, 0, w, h);
            float aspect = (float)info.windowWidth / (float)info.windowHeight;
            m_ProjMatrix = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);    // fov to 60 degrees
            GLint projMatLoc = glGetUniformLocation(m_Program, "projMat");
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix));
        }
};

MAIN(Bubacow);
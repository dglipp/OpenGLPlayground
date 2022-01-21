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

class Orbit : public App
{
    private:
        GLint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer[3];

        glm::vec3 m_Camera;
        glm::mat4 m_ProjMatrix;

        std::stack<glm::mat4> mvStack;

        geo::Sphere m_Planet;
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
            m_Planet = geo::Sphere();
            m_Texture = Texture("../../res/textures/earth.jpg");

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_Texture.getTextureID());

            std::vector<unsigned int> ind = m_Planet.getIndices();
            std::vector<glm::vec3> vert = m_Planet.getVertices();
            std::vector<glm::vec3> norm = m_Planet.getNormals();
            std::vector<glm::vec2> tex = m_Planet.getTexCoords();

            std::vector<float> posData;
            std::vector<float> texData;
            std::vector<float> normData;

            for (int i = 0; i < m_Planet.getNIndices(); ++i)
            {
                posData.push_back(vert[ind[i]].x);
                posData.push_back(vert[ind[i]].y);
                posData.push_back(vert[ind[i]].z);

                texData.push_back(tex[ind[i]].s);
                texData.push_back(tex[ind[i]].t);

                normData.push_back(norm[ind[i]].x);
                normData.push_back(norm[ind[i]].y);
                normData.push_back(norm[ind[i]].z);
            }

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

            glGenBuffers(3, m_Buffer);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, posData.size() * 4, &posData[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]);
            glBufferData(GL_ARRAY_BUFFER, texData.size() * 4, &texData[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[2]);
            glBufferData(GL_ARRAY_BUFFER, normData.size() * 4, &normData[0], GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(2);


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

            // SUN
            mvStack.push(mvStack.top());
            mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            mvStack.push(mvStack.top());
            mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)time, glm::vec3(1.0f, 0.0f, 0.0f));

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

            glDrawArrays(GL_TRIANGLES, 0,  m_Planet.getNIndices());
            mvStack.pop();

            // EARTH
            mvStack.push(mvStack.top());
            mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3((float)sin(time) * 4.0f, 0.0f, (float)cos(time) * 4.0f));
            
            mvStack.push(mvStack.top());
            mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)time, glm::vec3(0.0f, 1.0f, 0.0f));

            mvStack.push(mvStack.top());
            mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
            glDrawArrays(GL_TRIANGLES, 0,  m_Planet.getNIndices());
            mvStack.pop();
            mvStack.pop();

            // MOON
            mvStack.push(mvStack.top());
            mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, (float)sin(time) * 2.0f, (float)cos(time) * 2.0f));

            mvStack.push(mvStack.top());
            mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)time, glm::vec3(0.0f, 1.0f, 0.0f));

            mvStack.push(mvStack.top());
            mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
            glDrawArrays(GL_TRIANGLES, 0,  m_Planet.getNIndices());

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

MAIN(Orbit);
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
#include <INTERNAL/Light.h>
#include <INTERNAL/Material.h>
#include <INTERNAL/Loader.h>

class Gouraud : public App
{
    private:
        GLint m_Program;
        GLuint m_VAO;
        GLuint m_Buffer[3];

        glm::vec3 m_Camera;
        glm::mat4 m_ProjMatrix;

        geo::Mesh m_Mesh;
        light::Positional m_posLight;
        light::Ambient m_AmbientLight;
        mtl::BaseMtl m_GoldMtl;

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
            // mesh setup
            load::ObjLoader meshLoader("../../res/models/dragon.obj", "dragon");
            m_Mesh = meshLoader.loadMesh();

            std::vector<unsigned int> ind = m_Mesh.getIndices();
            std::vector<float> vert = m_Mesh.getVertexBuffer();
            std::vector<float> norm = m_Mesh.getNormalBuffer();

            // light setup
            m_posLight = light::Positional(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(5.0f, 2.0f, 2.0f));
            m_AmbientLight = light::Ambient(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

            // material setup
            m_GoldMtl = mtl::BaseMtl(glm::vec4(0.2473f, 0.1995f, 0.0745f, 1.0f), glm::vec4(0.7516f, 0.6065f, 0.2265f, 1.0f), glm::vec4(0.6283f, 0.5558f, 0.3661f, 1.0f), 51.2f);

            // shader setup
            std::vector<ShaderInfo> shaders =
            {
                {GL_VERTEX_SHADER, "../../res/shaders/gouraud.vert.glsl"},
                {GL_FRAGMENT_SHADER, "../../res/shaders/gouraud.frag.glsl"}
            };

            ShaderProgram program {shaders};
            m_Program = program.createProgram();
            glUseProgram(m_Program);
            
            // gpu data setup
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            glGenBuffers(3, m_Buffer);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, vert.size() * 4, &vert[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, m_Buffer[1]);
            glBufferData(GL_ARRAY_BUFFER, norm.size() * 4, &norm[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer[2]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);

            // camera setup
            m_Camera = glm::vec3(0, 10, 30);

            // Projection Matrix uniform
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
            GLint nMatLoc = glGetUniformLocation(m_Program, "normMat");

            glm::mat4 viewMat = glm::lookAt(m_Camera,
                                            glm::vec3(0, 0, 0),
                                            glm::vec3(0, 1, 0));

            glm::mat4 modelMat = glm::mat4(1.0f);
            glm::mat4 mvMat = viewMat * modelMat;
            glm::mat4 invTrMat = glm::transpose(glm::inverse(mvMat));

            glUniformMatrix4fv(mvMatLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
            glUniformMatrix4fv(nMatLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

            // setup lights
            glm::vec3 lightViewPos = glm::vec3(viewMat * glm::vec4(m_posLight.getLocation(), 1.0f));

            GLuint globAmbLoc = glGetUniformLocation(m_Program, "globalAmbient");
            GLuint ambLoc = glGetUniformLocation(m_Program, "light.ambient");
            GLuint diffuseLoc = glGetUniformLocation(m_Program, "light.diffuse");
            GLuint specularLoc = glGetUniformLocation(m_Program, "light.specular");
            GLuint posLoc = glGetUniformLocation(m_Program, "light.position");
            GLuint matAmbLoc = glGetUniformLocation(m_Program, "material.ambient");
            GLuint matDiffuseLoc = glGetUniformLocation(m_Program, "material.diffuse");
            GLuint matSpecularLoc = glGetUniformLocation(m_Program, "material.specular");
            GLuint matShininessLoc = glGetUniformLocation(m_Program, "material.shininess");

            glProgramUniform4fv(m_Program, globAmbLoc, 1, glm::value_ptr(m_AmbientLight.getAmbient()));
            glProgramUniform4fv(m_Program, ambLoc, 1, glm::value_ptr(m_posLight.getAmbient()));
            glProgramUniform4fv(m_Program, diffuseLoc, 1, glm::value_ptr(m_posLight.getDiffuse()));
            glProgramUniform4fv(m_Program, specularLoc, 1, glm::value_ptr(m_posLight.getSpecular()));
            glProgramUniform3fv(m_Program, posLoc, 1, glm::value_ptr(lightViewPos));
            glProgramUniform4fv(m_Program, matAmbLoc, 1, glm::value_ptr(m_GoldMtl.getAmbient()));
            glProgramUniform4fv(m_Program, matDiffuseLoc, 1, glm::value_ptr(m_GoldMtl.getDiffuse()));
            glProgramUniform4fv(m_Program, matSpecularLoc, 1, glm::value_ptr(m_GoldMtl.getSpecular()));
            glProgramUniform1f(m_Program, matShininessLoc, m_GoldMtl.getShininess());

            glDrawElements(GL_TRIANGLES, m_Mesh.getNIndices(), GL_UNSIGNED_INT, nullptr);
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

MAIN(Gouraud);
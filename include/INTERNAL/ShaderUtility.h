#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include <GL/glew.h>


struct ShaderInfo
{
    GLuint shaderType;
    std::string sourcePath;
};

class ShaderProgram
{
    private:
        std::vector<ShaderInfo> m_ShaderInfos;
        GLuint m_Program;

    private:
        /**
         * @brief Get source string from ShaderInfo object (uses only sourcePath).
         * 
         * @returns Return a string representing source.
         */
        std::string readSource(const ShaderInfo& shader) const;

        /**
         * Check compilation errors in given shader.
         */
        void printShaderLog(GLuint shaderPointer);
        
        /**
         * Check compilation errors in given program.
         */
        void printProgramLog();

        /**
         * Check opengl errors.
         */
        bool checkOpenGLError();


    public:
        ShaderProgram();
        ShaderProgram(ShaderInfo shader);
        ShaderProgram(std::vector<ShaderInfo> shaders);
        ~ShaderProgram();

        /**
         * @brief Compile, link shaders in program and returns pointer to program
         */
        GLuint createProgram();
};
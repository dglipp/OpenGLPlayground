#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>


struct ShaderInfo
{
    GLuint shaderType;
    std::string sourcePath; 
};

class ShaderLoader
{
    protected:
        std::vector<ShaderInfo> m_Shaders;

    protected:
        /**
         * @brief Get source string from ShaderInfo object (uses only sourcePath)
         * 
         * @returns Return a string representing source 
         */
        std::string getSource(const ShaderInfo & shader) const;

        /**
         * @brief Apply getSource for all ShaderInfo objects in vector
         * @returns A vector of string representing sources
         */
        std::vector<std::string> getSources(const std::vector<ShaderInfo> & shaders) const;

        /**
         * @brief Compile given shader. To be redefined in specialized subclasses
         * 
         * @param shader The shader to be compiled
         */

    public:
        ShaderLoader();
        ShaderLoader(ShaderInfo shader);
        ShaderLoader(std::vector<ShaderInfo> shaders);
        ~ShaderLoader();

        void addShader(ShaderInfo shader);
        virtual GLuint getProgram() const = 0;
};

class GlslLoader : public ShaderLoader
{
    public:
        GlslLoader();
        GlslLoader(ShaderInfo shader);
        GlslLoader(std::vector<ShaderInfo> shaders);
        ~GlslLoader();

        GLuint getProgram() const;
};
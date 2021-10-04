#include <INTERNAL/ShaderUtility.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::ShaderLoader(ShaderInfo shader)
    : m_Shaders{shader}
{
}

ShaderLoader::ShaderLoader(std::vector<ShaderInfo> shaders)
    : m_Shaders(shaders)
{
}

ShaderLoader::~ShaderLoader()
{
}

void ShaderLoader::addShader(ShaderInfo shader)
{
    m_Shaders.push_back(shader);
}

std::string ShaderLoader::getSource(const ShaderInfo & shader) const
{
    std::ifstream t(shader.sourcePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string shaderSource = buffer.str();
    return shaderSource;
}

std::vector<std::string> ShaderLoader::getSources(const std::vector<ShaderInfo> & shaders) const
{
    std::vector<std::string> shaderSources;
    for(const auto shader : shaders)
        shaderSources.push_back(ShaderLoader::getSource(shader));
    return shaderSources;
}

GlslLoader::GlslLoader()
    : ShaderLoader()
{
}

GlslLoader::GlslLoader(ShaderInfo shader)
    : ShaderLoader(shader)
{
}

GlslLoader::GlslLoader(std::vector<ShaderInfo> shaders)
    : ShaderLoader(shaders)
{
}

GlslLoader::~GlslLoader()
{
}

GLuint GlslLoader::getProgram() const
{
    GLuint program = glCreateProgram();
    GLsizei len;
    GLchar message[1024];
    std::vector<std::string> sources;
    for(const auto s : m_Shaders)
    {
        GLuint shaderName = glCreateShader(s.shaderType);
        sources.push_back(getSource(s));
        const GLchar * src = sources[sources.size()-1].c_str();
        glShaderSource(shaderName, 1, &src, nullptr);
        glCompileShader(shaderName);


        GLsizei len;
        GLchar message[1024];
        glGetShaderInfoLog(shaderName, 1024, &len, message);
        if (len) std::cout << message << std::endl;
        
        glAttachShader(program, shaderName);
        glDeleteShader(shaderName);
    }

    glLinkProgram(program);
    glGetProgramInfoLog(program, 1024, &len, message);
    if (len) std::cout << message << std::endl;

    return program;
}
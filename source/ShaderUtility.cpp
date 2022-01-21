#include <INTERNAL/ShaderUtility.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(ShaderInfo shader)
    : m_ShaderInfos {shader}
{
}

ShaderProgram::ShaderProgram(std::vector<ShaderInfo> shaderInfos)
    : m_ShaderInfos(shaderInfos)
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::printShaderLog(GLuint shaderPointer)
{
    GLsizei len;
    GLchar message[1024];
    glGetShaderInfoLog(shaderPointer, 1024, &len, message);
    if (len) std::cout << "[GLSL COMPILATION ERROR]: " << message << std::endl;
}

void ShaderProgram::printProgramLog()
{
    GLsizei len;
    GLchar message[1024];
    glGetProgramInfoLog(m_Program, 1024, &len, message);
    if (len) std::cout << "[GLSL LINK ERROR]: " << message << std::endl;
}

bool ShaderProgram::checkOpenGLError()
{
    bool errorFound = false;
    int glError = glGetError();

    while(glError != GL_NO_ERROR)
    {
        std::cout << "[GL ERROR]: " << glError << '\n';
        errorFound = true;
        glError = glGetError();
    }
    return errorFound;
}

std::string ShaderProgram::readSource(const ShaderInfo & shader) const
{
    std::ifstream t(shader.sourcePath);
    if(t.fail())
        std::cout << "[IO ERROR]: File not found.\n";
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string shaderSource = buffer.str();
    return shaderSource;
}

GLuint ShaderProgram::createProgram()
{
    m_Program = glCreateProgram();

    std::vector<std::string> sources;
    for(const auto s : m_ShaderInfos)
    {
        sources.push_back(readSource(s));

        GLuint shaderPointer = glCreateShader(s.shaderType);
        const GLchar * src = sources[sources.size()-1].c_str();
        glShaderSource(shaderPointer, 1, &src, nullptr);
        glCompileShader(shaderPointer);
        checkOpenGLError();
        printShaderLog(shaderPointer);

        glAttachShader(m_Program, shaderPointer);
        glDeleteShader(shaderPointer);
    }

    glLinkProgram(m_Program);
    printProgramLog();

    return m_Program;
}
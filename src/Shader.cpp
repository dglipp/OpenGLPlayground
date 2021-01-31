#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <INTERNAL/Shader.h>
#include <INTERNAL/Renderer.h>

Shader::Shader()
{
}

Shader::Shader(const std::string &filepath)
    : m_Filepath(filepath), m_ShaderID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_ShaderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader & Shader::operator=(Shader &&shader)
{
    if (this == &shader)
        return *this;

    m_Filepath = std::move(shader.m_Filepath);
    m_ShaderID = shader.m_ShaderID;
    shader.m_ShaderID = 0;
    m_UniformLocationCache = std::move(shader.m_UniformLocationCache);
    
    return *this;
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_ShaderID));
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
        std::cout << "[INTERNAL ERROR]: Shader program file not found" << std::endl;
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // char *message = (char *)alloca(length * sizeof(char));
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" << 
            (type == GL_VERTEX_SHADER ? " vertex " : " fragment ") <<
            "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}


void Shader::Bind() const
{
    GLCall(glUseProgram(m_ShaderID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    Bind();
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    Unbind();
}

void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2)
{
    Bind();
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    Unbind();
}

void Shader::SetUniform1f(const std::string &name, float value)
{
    Bind();
    GLCall(glUniform1f(GetUniformLocation(name), value));
    Unbind();
}

void Shader::SetUniform1i(const std::string &name, int value)
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), value));
    Unbind();
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    Bind();
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    Unbind();
}

int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return  m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_ShaderID, name.c_str()));
    if (location == -1)
        std::cout << "[WARNING]: uniform " << name << " doesn't exist." << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

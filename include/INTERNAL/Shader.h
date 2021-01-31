#pragma once

#include <string>
#include <unordered_map>

#include <VENDOR/GLM/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        std::string m_Filepath;
        unsigned int m_ShaderID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        int GetUniformLocation(const std::string &name);
        bool CompileShader();
        ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string &source);
        unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    public:
        Shader();
        Shader(const std::string &filepath);
        ~Shader();
        Shader &operator=(Shader &&shader);

        void Bind() const;
        void Unbind() const;

        void SetUniform1f(const std::string &name, float value);
        void SetUniform3f(const std::string &name, float v0, float v1, float v2);
        void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
        void SetUniform1i(const std::string &name, int value);

        void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

};
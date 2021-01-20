#include <INTERNAL/Renderer.h>
#include <iostream>

void GLClearError()
{
    while (glGetError());
}

bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OPENGL ERROR]: " << error << std::endl <<
            "in file " << file << std::endl <<
            "in function " << function << std::endl <<
            "at line " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray &va, const ElementBuffer &eb, const Shader &shader) const
{
    Clear();
    shader.Bind();
    va.Bind();
    eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ResetClearColor() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

void Renderer::SetClearColor(const float  *color) const
{
    GLCall(glClearColor(color[0], color[1], color[2], color[3]));
}
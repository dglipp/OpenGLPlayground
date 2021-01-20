#include <INTERNAL/VertexBuffer.h>
#include <INTERNAL/Renderer.h>

VertexBuffer::VertexBuffer()
{
    GLCall(glGenBuffers(1, &m_VBO));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_VBO))
}

void VertexBuffer::SetBuffer(const void *data, unsigned int size)
{
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
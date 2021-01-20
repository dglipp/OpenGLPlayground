#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/Renderer.h>

ElementBuffer::ElementBuffer()
{
    GLCall(glGenBuffers(1, &m_IBO));
}

ElementBuffer::~ElementBuffer()
{
    GLCall(glDeleteBuffers(1, &m_IBO))
}

void ElementBuffer::SetBuffer(unsigned int const *data, unsigned int size)
{
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    m_Count = size / sizeof(unsigned int);
}

void ElementBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
}

void ElementBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
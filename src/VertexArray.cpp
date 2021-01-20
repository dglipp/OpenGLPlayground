#include <INTERNAL/VertexArray.h>
#include <INTERNAL/Renderer.h>
#include <INTERNAL/VertexBufferLayout.h>

#include <iostream>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_VAO));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_VAO));
}

void VertexArray::Bind() const 
{
    GLCall(glBindVertexArray(m_VAO));
}

void VertexArray::Unbind() const 
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{

    for (const auto & [ key, value ] : layout)
    {
        GLCall(glVertexAttribPointer(value.index, value.count, value.type, value.normalized, layout.getStride(), (const void *) (long int) value.position));
        GLCall(glEnableVertexAttribArray(value.index));
    }
    Unbind();
}
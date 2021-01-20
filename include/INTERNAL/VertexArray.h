#pragma once

#include <INTERNAL/VertexBuffer.h>

class VertexBufferLayout;

class VertexArray
{
    private:
        unsigned int m_VAO;

    public:
        VertexArray();
        ~VertexArray();
        
        void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

        void Bind() const;
        void Unbind() const;
};
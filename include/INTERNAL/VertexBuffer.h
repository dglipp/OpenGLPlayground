#pragma once

class VertexBuffer
{
    private:
        unsigned int m_VBO;
    
    public:
        VertexBuffer();
        ~VertexBuffer();

        void SetBuffer(const void *data, unsigned int size);
        void Bind() const;
        void Unbind() const;

};
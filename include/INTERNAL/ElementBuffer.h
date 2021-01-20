#pragma once

class ElementBuffer
{
    private:
        unsigned int m_IBO;
        unsigned int m_Count;
    public:
        ElementBuffer();
        ~ElementBuffer();

        void Bind() const;
        void Unbind() const;

        void SetBuffer(unsigned int const *data, unsigned int size);
        inline unsigned int GetCount() const { return m_Count; }
};
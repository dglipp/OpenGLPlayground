#pragma once

#include <vector>
#include <INTERNAL/Renderer.h>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned short index;
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    int position;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }

        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    unsigned int m_Stride;
    std::unordered_map<std::string, VertexBufferElement> m_Attribs;

public:
    VertexBufferLayout()
        : m_Stride(0) {}

    template <typename T>
    bool Push(unsigned int count, const std::string &name);

    inline unsigned int getStride() const { return m_Stride; }
    inline const VertexBufferElement GetElement(const std::string &attribName) const {
        auto element = m_Attribs.find(attribName);
        if(element != m_Attribs.end())
            return m_Attribs.find(attribName) -> second;
        return {0, 0,0,0, -1};
    }

    inline auto begin() const { return m_Attribs.begin(); }
    inline auto begin() { return m_Attribs.begin(); }

    inline auto end() const { return m_Attribs.end(); }
    inline auto end() { return m_Attribs.end(); }
};

template <>
inline bool VertexBufferLayout::Push<float>(unsigned int count, const std::string &name)
{
    if (m_Attribs.find(name) == m_Attribs.end())
    {
        unsigned short index = m_Attribs.size();
        m_Attribs[name] = {index, GL_FLOAT, count, GL_FALSE, (int) m_Stride};
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
        return false;
    }
    return true;
}

template <>
inline bool VertexBufferLayout::Push<unsigned int>(unsigned int count, const std::string &name)
{
    if (m_Attribs.find(name) == m_Attribs.end())
    {
        m_Attribs[name] = {(unsigned short) m_Attribs.size(), GL_UNSIGNED_INT, count, GL_FALSE, (int) m_Stride};
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
        return false;
    }
    return true;
}

template <>
inline bool VertexBufferLayout::Push<unsigned char>(unsigned int count, const std::string &name)
{
    if (m_Attribs.find(name) == m_Attribs.end())
    {
        m_Attribs[name] = {(unsigned short) m_Attribs.size(), GL_UNSIGNED_BYTE, count, GL_FALSE, (int) m_Stride};
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
        return false;
    }
    return true;
}
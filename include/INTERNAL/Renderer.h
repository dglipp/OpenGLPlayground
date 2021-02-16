#pragma once

#include <GL/glew.h>
#include <INTERNAL/ElementBuffer.h>
#include <INTERNAL/VertexArray.h>
#include <INTERNAL/Shader.h>

#define ASSERT(x) if (!(x)) __builtin_trap()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{
    public:
        void Draw(const VertexArray &va, const ElementBuffer &ib, const Shader &shader) const;
        void Clear() const;
        void ResetClearColor() const;
        void SetClearColor(const float *color) const;
};
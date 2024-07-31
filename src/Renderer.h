#pragma once
#include <GL/glew.h>
#include <cassert>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())

void GLClearError();

bool GLCheckError();

class Renderer
{
public :
    void Clear() const;
    void Draw(const VertexArray& _va, const IndexBuffer& _ib, Shader& _shaderBasic, Shader& _shaderTess) const;
};
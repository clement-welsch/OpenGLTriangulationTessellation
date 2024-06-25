#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <cassert>

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())

void GLClearError();

bool GLCheckError();

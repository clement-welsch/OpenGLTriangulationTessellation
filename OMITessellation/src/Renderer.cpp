#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError()
{
    while (GLenum error = glGetError())
    {

        std::cout << "[OpenGL Error] ";
        switch (error) {
        case GL_INVALID_ENUM:
            std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
            break;
        case GL_INVALID_VALUE:
            std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
            break;
        case GL_INVALID_OPERATION:
            std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
            break;
        case GL_STACK_UNDERFLOW:
            std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            break;
        case GL_STACK_OVERFLOW:
            std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
            break;
        default:
            std::cout << "Unrecognized error" << error;
        }
        std::cout << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& _va, const IndexBuffer&  _ib, const Shader& _shader) const
{
    _shader.Bind();
    _ib.Bind();
    _va.Bind();

    bool wireframe = true;

    if (wireframe)
    {
        GLCall(glPointSize(10.0f));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    {
        /*GLCall(glPatchParameteri(GL_PATCH_VERTICES, 4));
        GLCall(glDrawElements(GL_PATCHES, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));*/
    }

    {

        GLCall(glPointSize(10.0f));
        GLCall(glDrawElements(GL_POINTS, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));
        GLCall(glDrawElements(GL_LINE_STRIP, _ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}

#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* _data, unsigned int _size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

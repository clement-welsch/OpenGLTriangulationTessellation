#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* _data, unsigned int _size);
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	unsigned int m_RendererID;
};
#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* _data, unsigned int _size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_rendererID;
};
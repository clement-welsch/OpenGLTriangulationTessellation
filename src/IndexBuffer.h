#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* _data, unsigned int _count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }
private:
	unsigned int m_rendererID;
	unsigned int m_count;
};
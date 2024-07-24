#pragma once

#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int m_type;
	unsigned int m_count;
	unsigned char m_normalized;

	VertexBufferElement(unsigned int _type, unsigned int _count, bool _normalized) : m_type(_type), m_count(_count), m_normalized(_normalized)
	{}

	static unsigned int GetSizeOfType(unsigned int _type)
	{
		switch (_type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			default: ASSERT(false); return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template <typename T>
	void Push(unsigned int _count)
	{
		ASSERT(false);
	}

	template<>
	void Push<float>(unsigned int _count)
	{
		m_elements.push_back({ GL_FLOAT, _count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * _count;
	}

	template<>
	void Push<unsigned int>(unsigned int _count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, _count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * _count;
	}

	template<>
	void Push<unsigned char>(unsigned int _count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, _count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * _count;
	}

	inline unsigned int GetStride() const { return m_stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return m_elements; }

private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;

};
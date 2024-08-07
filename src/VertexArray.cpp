#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& _vb, const VertexBufferLayout& layout)
{
	Bind();
	_vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	unsigned int offest = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(i, element.m_count, element.m_type, element.m_normalized, layout.GetStride(), (const void*) offest));
		offest += element.m_count * VertexBufferElement::GetSizeOfType(element.m_type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

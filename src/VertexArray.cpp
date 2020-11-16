#include "VertexArray.h"
#include "Renderer.h"
#include <iostream>
VertexArray::VertexArray()
{
	glCall(glGenVertexArrays(1, &m_RenderedID)); //maak vertex array
	
}

VertexArray::~VertexArray()
{
	glCall(glDeleteVertexArrays(1, &m_RenderedID));
}
//neemt een vertex buffer en een layout
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements(); 
	unsigned int offset = 0;
	
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i]; 
		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element.count, element.type,
			   element.normilized, layout.GetStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type); 
	}
}
void VertexArray::Bind() const
{
	glCall(glBindVertexArray(m_RenderedID));
}
void VertexArray::Unbind() const
{
	glCall(glBindVertexArray(0));
}
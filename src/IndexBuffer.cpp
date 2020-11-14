#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    glCall(glGenBuffers(1, &m_RendererID));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //bind buffer
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // insert data

}

IndexBuffer::~IndexBuffer()
{
    glCall(glDeleteBuffers(1, &m_RendererID)); //delete 1 buffer met aangegeven ID
}

void IndexBuffer::Bind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //bind buffer
}

void IndexBuffer::Unbind() const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); //unbind buffer
}

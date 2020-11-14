#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glCall(glGenBuffers(1, &m_RendererID));
    std::cout << m_RendererID << std::endl; 
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //bind buffer
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // insert data

}

VertexBuffer::~VertexBuffer()
{
    glCall(glDeleteBuffers(1, &m_RendererID)); //delete 1 buffer met aangegeven ID
}

void VertexBuffer::Bind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //bind buffer
}

void VertexBuffer::Unbind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //unbind buffer
}

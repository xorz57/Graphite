/// @author Georgios Fotopoulos

#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer() { glGenBuffers(1, &m_ID); }

IndexBuffer::~IndexBuffer() noexcept { glDeleteBuffers(1, &m_ID); }

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }

void IndexBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

GLuint IndexBuffer::GetID() const { return m_ID; }

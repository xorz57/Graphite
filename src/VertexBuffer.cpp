/// @author Georgios Fotopoulos

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_ID); }

VertexBuffer::~VertexBuffer() noexcept { glDeleteBuffers(1, &m_ID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

GLuint VertexBuffer::GetID() const { return m_ID; }

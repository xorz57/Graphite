/// @author Georgios Fotopoulos

#include "VertexArray.hpp"

VertexArray::VertexArray() { glGenVertexArrays(1, &m_ID); }

VertexArray::~VertexArray() noexcept { glDeleteVertexArrays(1, &m_ID); }

void VertexArray::Bind() const { glBindVertexArray(m_ID); }

void VertexArray::Unbind() { glBindVertexArray(0); }

void VertexArray::SetVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                         const void *pointer) const {
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

GLuint VertexArray::GetID() const { return m_ID; }

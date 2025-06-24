/// @author Georgios Fotopoulos

#pragma once

#include <glad/glad.h>

class VertexArray final {
public:
  VertexArray();
  ~VertexArray() noexcept;
  void Bind() const;
  static void Unbind();
  void SetVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                              const void *pointer) const;
  [[nodiscard]] GLuint GetID() const;

private:
  GLuint m_ID{};
};

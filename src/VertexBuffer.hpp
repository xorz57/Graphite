/// @author Georgios Fotopoulos

#pragma once

#include <vector>

#include <glad/glad.h>

class VertexBuffer final {
public:
  VertexBuffer();
  ~VertexBuffer() noexcept;
  void Bind() const;
  static void Unbind();
  template <typename T> void Upload(const std::vector<T> &vertices, GLenum usage = GL_STATIC_DRAW) const {
    Bind();
    const GLsizeiptr size{static_cast<GLsizeiptr>(vertices.size() * sizeof(T))};
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), usage);
  }
  [[nodiscard]] GLuint GetID() const;

private:
  GLuint m_ID{};
};

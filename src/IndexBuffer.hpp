/// @author Georgios Fotopoulos

#pragma once

#include <vector>

#include <glad/glad.h>

class IndexBuffer final {
public:
  IndexBuffer();
  ~IndexBuffer() noexcept;
  void Bind() const;
  GLuint GetID() const;
  static void Unbind();
  template <typename T> void Upload(const std::vector<T> &indices, GLenum usage = GL_STATIC_DRAW) {
    Bind();
    GLsizeiptr size{static_cast<GLsizeiptr>(indices.size() * sizeof(T))};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), usage);
  }

private:
  GLuint m_ID{};
};

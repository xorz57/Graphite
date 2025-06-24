/// @author Georgios Fotopoulos

#pragma once

#include <string>
#include <string_view>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <glad/glad.h>

class Shader final {
public:
  Shader(const std::string vShaderPath, const std::string fShaderPath);
  ~Shader();
  void Use() const;
  void SetFloat(std::string_view name, float value) const;
  void SetVec2(std::string_view name, const glm::vec2 &v) const;
  void SetVec3(std::string_view name, const glm::vec3 &v) const;
  void SetVec4(std::string_view name, const glm::vec4 &v) const;
  void SetMat2(std::string_view name, const glm::mat2 &m) const;
  void SetMat3(std::string_view name, const glm::mat3 &m) const;
  void SetMat4(std::string_view name, const glm::mat4 &m) const;

private:
  [[nodiscard]] std::string LoadShader(const std::string_view path) const;
  [[nodiscard]] GLuint Compile(GLenum type, const std::string_view sv) const;
  [[nodiscard]] GLuint Link(GLuint vShader, GLuint fShader) const;
  [[nodiscard]] GLint GetUniformLocation(const std::string_view name) const;

  const std::string_view m_VShaderPath;
  const std::string_view m_FShaderPath;
  GLuint m_Program{};
};

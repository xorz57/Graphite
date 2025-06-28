/// @author Georgios Fotopoulos

#include "Shader.hpp"

#include <fstream>
#include <print>
#include <sstream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string vShaderPath, const std::string fShaderPath)
    : m_VShaderPath(std::move(vShaderPath)), m_FShaderPath(std::move(fShaderPath)) {
  std::string v_shader_source{LoadShader(m_VShaderPath)};
  std::string f_shader_source{LoadShader(m_FShaderPath)};

  GLuint v_shader{Compile(GL_VERTEX_SHADER, v_shader_source)};
  GLuint f_shader{Compile(GL_FRAGMENT_SHADER, f_shader_source)};

  m_Program = Link(v_shader, f_shader);
}

Shader::~Shader() { glDeleteProgram(m_Program); }

void Shader::Use() const { glUseProgram(m_Program); }

std::string Shader::LoadShader(const std::string_view path) const {
  std::ifstream ifs(path.data());
  if (!ifs) {
    std::exit(EXIT_FAILURE);
  }

  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

GLuint Shader::Compile(GLenum type, const std::string_view sv) const {
  GLuint shader{glCreateShader(type)};
  const char *str = sv.data();
  glShaderSource(shader, 1, &str, nullptr);
  glCompileShader(shader);

  GLint compile_status{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
  if (!compile_status) {
    GLint info_log_length{};
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> log(static_cast<std::size_t>(info_log_length));
    glGetShaderInfoLog(shader, info_log_length, nullptr, log.data());
    std::println("{}", log.data());
    std::exit(EXIT_FAILURE);
  }

  return shader;
}

GLuint Shader::Link(GLuint vertexShader, GLuint fragmentShader) const {
  GLuint program{glCreateProgram()};
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint link_status{};
  glGetProgramiv(program, GL_LINK_STATUS, &link_status);
  if (!link_status) {
    GLint info_log_length{};
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
    std::vector<char> log(static_cast<std::size_t>(info_log_length));
    glGetProgramInfoLog(program, info_log_length, nullptr, log.data());
    std::println("{}", log.data());
    std::exit(EXIT_FAILURE);
  }

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

GLint Shader::GetUniformLocation(const std::string_view name) const {
  return glGetUniformLocation(m_Program, name.data());
}

void Shader::SetFloat(std::string_view name, float v0) const {
  const GLint location{GetUniformLocation(name)};
  glUniform1f(location, v0);
}

void Shader::SetVec2(std::string_view name, const glm::vec2 &v) const {
  const GLint location{GetUniformLocation(name)};
  glUniform2fv(location, 1, glm::value_ptr(v));
}

void Shader::SetVec3(std::string_view name, const glm::vec3 &v) const {
  const GLint location{GetUniformLocation(name)};
  glUniform3fv(location, 1, glm::value_ptr(v));
}

void Shader::SetVec4(std::string_view name, const glm::vec4 &v) const {
  const GLint location{GetUniformLocation(name)};
  glUniform4fv(location, 1, glm::value_ptr(v));
}

void Shader::SetMat2(std::string_view name, const glm::mat2 &m) const {
  const GLint location{GetUniformLocation(name)};
  glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetMat3(std::string_view name, const glm::mat3 &m) const {
  const GLint location{GetUniformLocation(name)};
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetMat4(std::string_view name, const glm::mat4 &m) const {
  const GLint location{GetUniformLocation(name)};
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

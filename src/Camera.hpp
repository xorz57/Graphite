/// @author Georgios Fotopoulos

#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera final {
public:
  Camera() = default;
  void Update(float deltaTime);
  void SetPosition(const glm::vec3 &position);
  [[nodiscard]] glm::vec3 GetPosition() const;
  [[nodiscard]] glm::mat4 GetView() const;
  [[nodiscard]] glm::mat4 GetProjection(float aspect) const;

private:
  glm::vec3 m_Position;
  glm::vec3 m_Front{0.0f, 0.0f, -1.0f};
  glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
  glm::vec3 m_Right{1.0f, 0.0f, 0.0f};
  float m_Yaw{-90.0f};
  float m_Pitch{0.0f};
  float m_Speed{1.0f};
  float m_Sensitivity{0.1f};
  float m_FOV{45.0f};
  float m_Near{0.1f};
  float m_Far{100.0f};
  bool m_CursorCaptured{false};
};

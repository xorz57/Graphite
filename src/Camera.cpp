/// @author Georgios Fotopoulos

#include "Camera.hpp"

#include <cstdlib>

#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void Camera::Update(float deltaTime) {
  GLFWwindow *window{glfwGetCurrentContext()};
  if (!window) {
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    const float factor{glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 2.0f : 1.0f};
    const float distance{deltaTime * m_Speed * factor};

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      m_Position += distance * m_Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      m_Position -= distance * m_Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      m_Position -= distance * m_Right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      m_Position += distance * m_Right;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      m_Position.y += distance;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
      m_Position.y -= distance;

    int window_w{};
    int window_h{};
    glfwGetWindowSize(window, &window_w, &window_h);

    double center_x{0.5 * window_w};
    double center_y{0.5 * window_h};

    if (!m_CursorCaptured) {
      glfwSetCursorPos(window, center_x, center_y);
      m_CursorCaptured = true;
    }

    double cursor_x{};
    double cursor_y{};
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    double dx{cursor_x - center_x};
    double dy{cursor_y - center_y};

    m_Yaw += static_cast<float>(dx) * m_Sensitivity;
    m_Pitch -= static_cast<float>(dy) * m_Sensitivity;

    if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;

    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
    direction.y = glm::sin(glm::radians(m_Pitch));
    direction.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(direction);
    m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));

    glfwSetCursorPos(window, center_x, center_y);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    m_CursorCaptured = false;
  }
}

void Camera::SetPosition(const glm::vec3 &position) { m_Position = position; }

glm::vec3 Camera::GetPosition() const { return m_Position; }

glm::mat4 Camera::GetView() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }

glm::mat4 Camera::GetProjection(float aspect) const {
  return glm::perspective(glm::radians(m_FOV), aspect, m_Near, m_Far);
}

/// @author Georgios Fotopoulos

#pragma once

#include <glm/vec3.hpp>

struct Material final {
  glm::vec3 ambient{};
  glm::vec3 diffuse{};
  glm::vec3 specular{};
  float shininess{};
};

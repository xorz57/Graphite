/// @author Georgios Fotopoulos

#pragma once

#include <string>

class Layer {
public:
  explicit Layer(std::string name) : m_Name(std::move(name)) {}
  virtual ~Layer() = default;
  virtual void OnAttach() = 0;
  virtual void OnDetach() = 0;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnRenderUI() = 0;
  void SetName(const std::string name);
  [[nodiscard]] const std::string &GetName() const;

private:
  std::string m_Name;
};

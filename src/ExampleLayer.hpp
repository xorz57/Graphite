/// @author Georgios Fotopoulos

#include "Layer.hpp"

#include <cstdint>
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "IndexBuffer.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class ExampleLayer final : public Layer {
public:
  ExampleLayer();
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float deltaTime) override;
  void OnRenderUI() override;

private:
  Camera m_Camera;
  std::unique_ptr<Shader> m_LitShader;
  std::unique_ptr<Shader> m_LightShader;
  Light m_Light{
      glm::vec3(1.0f, 1.0f, 1.0f),
      glm::vec3(1.0f, 1.0f, 1.0f),
      glm::vec3(1.0f, 1.0f, 1.0f),
  };
  Material m_Material{
      glm::vec3(0.25f, 0.25f, 0.75f),
      glm::vec3(0.25f, 0.25f, 0.75f),
      glm::vec3(0.25f, 0.25f, 0.75f),
      32.0f,
  };
  const std::vector<Vertex> m_Vertices{
      // Front Face
      {{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
      {{+0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
      {{+0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
      {{-0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},

      // Back Face
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
      {{+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
      {{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
      {{-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},

      // Left Face
      {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
      {{-0.5f, -0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}},
      {{-0.5f, +0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}},
      {{-0.5f, +0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},

      // Right Face
      {{+0.5f, -0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}},
      {{+0.5f, -0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}},
      {{+0.5f, +0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}},
      {{+0.5f, +0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}},

      // Bottom Face
      {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
      {{+0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
      {{+0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}},
      {{-0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}},

      // Top Face
      {{-0.5f, +0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}},
      {{+0.5f, +0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}},
      {{+0.5f, +0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}},
      {{-0.5f, +0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}},
  };
  const std::vector<GLuint> m_Indices{
      0,  1,  2,  2,  3,  0,  // Front Face
      4,  5,  6,  6,  7,  4,  // Back Face
      8,  9,  10, 10, 11, 8,  // Left Face
      12, 13, 14, 14, 15, 12, // Right Face
      16, 17, 18, 18, 19, 16, // Bottom Face
      20, 21, 22, 22, 23, 20, // Top Face
  };
  std::unique_ptr<VertexArray> m_VertexArray;
  std::unique_ptr<VertexBuffer> m_VertexBuffer;
  std::unique_ptr<IndexBuffer> m_IndexBuffer;
  std::uint64_t m_Frame{};
  double m_DeltaTime{};
  bool m_Wireframe{false};
};

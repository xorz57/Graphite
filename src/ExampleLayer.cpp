/// @author Georgios Fotopoulos

#include "ExampleLayer.hpp"

#include <cinttypes>

#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <implot.h>

ExampleLayer::ExampleLayer() : Layer("ExampleLayer") {
  m_Camera.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));

  m_LitShader = std::make_unique<Shader>("assets/shaders/lit.vert.glsl", "assets/shaders/lit.frag.glsl");
  m_LightShader = std::make_unique<Shader>("assets/shaders/light.vert.glsl", "assets/shaders/light.frag.glsl");

  m_VertexArray = std::make_unique<VertexArray>();
  m_VertexBuffer = std::make_unique<VertexBuffer>();
  m_IndexBuffer = std::make_unique<IndexBuffer>();

  m_VertexArray->Bind();
  m_VertexBuffer->Upload(m_Vertices);
  m_IndexBuffer->Upload(m_Indices);
  m_VertexArray->SetVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                        reinterpret_cast<void *>(offsetof(Vertex, position)));
  m_VertexArray->SetVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                        reinterpret_cast<void *>(offsetof(Vertex, normal)));
  VertexArray::Unbind();
}

void ExampleLayer::OnAttach() {}

void ExampleLayer::OnDetach() {}

void ExampleLayer::OnUpdate(float deltaTime) {
  ++m_Frame;
  m_DeltaTime = deltaTime;

  GLFWwindow *window{glfwGetCurrentContext()};

  GLsizei window_w{};
  GLsizei window_h{};
  glfwGetFramebufferSize(window, &window_w, &window_h);

  const float window_a{static_cast<float>(window_w) / static_cast<float>(window_h)};

  if (m_Wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  m_Camera.Update(deltaTime);

  const double t{glfwGetTime()};
  m_Light.position = glm::vec3(4.0f * glm::sin(static_cast<float>(t)), 4.0f, 4.0f * glm::cos(static_cast<float>(t)));

  m_LightShader->Use();

  m_LightShader->SetMat4("u_View", m_Camera.GetView());
  m_LightShader->SetMat4("u_Projection", m_Camera.GetProjection(window_a));

  {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Light.position);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    m_LightShader->SetMat4("u_Model", model);
  }

  m_LightShader->SetVec3("u_Light.position", m_Light.position);
  m_LightShader->SetVec3("u_Light.ambient", m_Light.ambient);
  m_LightShader->SetVec3("u_Light.diffuse", m_Light.diffuse);
  m_LightShader->SetVec3("u_Light.specular", m_Light.specular);

  m_VertexArray->Bind();
  glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(m_Indices.size()), GL_UNSIGNED_INT,
                 static_cast<void *>(nullptr));
  m_VertexArray->Unbind();

  m_LitShader->Use();

  m_LitShader->SetMat4("u_View", m_Camera.GetView());
  m_LitShader->SetMat4("u_Projection", m_Camera.GetProjection(window_a));

  m_LitShader->SetVec3("u_Light.position", m_Light.position);
  m_LitShader->SetVec3("u_Light.ambient", m_Light.ambient);
  m_LitShader->SetVec3("u_Light.diffuse", m_Light.diffuse);
  m_LitShader->SetVec3("u_Light.specular", m_Light.specular);

  m_LitShader->SetVec3("u_CameraPosition", m_Camera.GetPosition());

  m_LitShader->SetVec3("u_Material.ambient", m_Material.ambient);
  m_LitShader->SetVec3("u_Material.diffuse", m_Material.diffuse);
  m_LitShader->SetVec3("u_Material.specular", m_Material.specular);
  m_LitShader->SetFloat("u_Material.shininess", m_Material.shininess);

  {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    m_LitShader->SetMat4("u_Model", model);
  }

  m_VertexArray->Bind();
  glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(m_Indices.size()), GL_UNSIGNED_INT,
                 static_cast<void *>(nullptr));
  m_VertexArray->Unbind();
}

void ExampleLayer::OnRenderUI() {
  ImGui::Begin("Statistics");
  if (ImGui::BeginTable("##statistics_table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
    ImGui::TableNextColumn();
    ImGui::Text("Frame");
    ImGui::TableNextColumn();
    ImGui::Text("%" PRIu64, m_Frame);

    ImGui::TableNextColumn();
    ImGui::Text("Delta Time");
    ImGui::TableNextColumn();
    ImGui::Text("%.8f", m_DeltaTime);

    ImGui::TableNextColumn();
    ImGui::Text("FPS");
    ImGui::TableNextColumn();
    ImGui::Text("%.8f", 1 / m_DeltaTime);

    ImGui::EndTable();
  }
  ImGui::End();

  ImGui::Begin("Material");
  ImGui::ColorEdit3("Ambient", (float *)&m_Material.ambient);
  ImGui::ColorEdit3("Diffuse", (float *)&m_Material.diffuse);
  ImGui::ColorEdit3("Specular", (float *)&m_Material.specular);
  ImGui::DragFloat("Shininess", &m_Material.shininess, 1.0f, 0.0f, 128.0f);
  ImGui::End();

  ImGui::Begin("Light");
  ImGui::ColorEdit3("Ambient", (float *)&m_Light.ambient);
  ImGui::ColorEdit3("Diffuse", (float *)&m_Light.diffuse);
  ImGui::ColorEdit3("Specular", (float *)&m_Light.specular);
  ImGui::End();

  ImGui::Begin("Settings");
  ImGui::Checkbox("Wireframe", &m_Wireframe);
  ImGui::End();
}

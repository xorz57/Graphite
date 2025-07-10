/// @author Georgios Fotopoulos

#include "UILayer.hpp"

#include <cstdlib>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

UILayer::UILayer() : Layer("UILayer") {}

void UILayer::OnAttach() {
  GLFWwindow *window{glfwGetCurrentContext()};
  if (!window) {
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io{ImGui::GetIO()};
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style{ImGui::GetStyle()};
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void UILayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UILayer::OnUpdate(float deltaTime) { static_cast<void>(deltaTime); }

void UILayer::OnRenderUI() {}

void UILayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void UILayer::End() {
  ImGui::Render();

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO &io{ImGui::GetIO()};
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *windowBackup{glfwGetCurrentContext()};
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(windowBackup);
  }
}

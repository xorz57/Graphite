/// @author Georgios Fotopoulos

#include <cstdlib>
#include <print>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ExampleLayer.hpp"
#include "UILayer.hpp"

static void ErrorCallback(const int error, const char *description) {
  std::println("Error Code {}: {}", error, description);
}

int main() {
  glfwSetErrorCallback(ErrorCallback);

  if (!glfwInit()) {
    std::exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_SAMPLES, 8);

  GLFWwindow *window{glfwCreateWindow(800, 600, "Graphite", nullptr, nullptr)};
  if (window == nullptr) {
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(0);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    glfwDestroyWindow(window);
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  std::println("OpenGL Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
  std::println("OpenGL Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
  std::println("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
  std::println("OpenGL Shading Language Version: {}",
               reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  std::unique_ptr<UILayer> ui_layer{std::make_unique<UILayer>()};
  std::unique_ptr<Layer> example_layer{std::make_unique<ExampleLayer>()};

  ui_layer->OnAttach();
  example_layer->OnAttach();

  float t0{static_cast<float>(glfwGetTime())};

  while (!glfwWindowShouldClose(window)) {
    const float t1{static_cast<float>(glfwGetTime())};
    const float dt{t1 - t0};
    t0 = t1;

    glfwPollEvents();

    GLsizei window_w{};
    GLsizei window_h{};
    glfwGetFramebufferSize(window, &window_w, &window_h);

    glViewport(0, 0, window_w, window_h);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    example_layer->OnUpdate(dt);

    ui_layer->Begin();
    example_layer->OnRenderUI();
    ui_layer->End();

    glfwSwapBuffers(window);
  }

  example_layer->OnDetach();
  ui_layer->OnDetach();

  example_layer.reset();
  ui_layer.reset();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

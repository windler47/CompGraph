#define GL_SILENCE_DEPRECATION // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <set>
#include "helpers.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "GlObject.hpp"

int main() {
  int windowWidth = 640;
  int windowHeight = 480;
  GLFWwindow *window = prepareWindow(windowWidth, windowHeight, "Honor");
  loadGl();

  // configure gl
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Camera camera = Camera(glm::vec3(-10.0f, -10.0f, -10.0f));
  Shader shader("shaders/color_vertex.glsl", "shaders/color_fragment.glsl");
  shader.Use();
  shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));

  shader.setVec3("light.direction", 1.0f, 1.0f, 1.0f);

  shader.setFloat("light.ambient", 0.05f);
  shader.setFloat("light.diffuse", 0.5f);
  shader.setFloat("light.specular", 0.9f);

  ColoredVertex vertices[] = {
      // rear
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

      // front
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

      // right
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

      // top
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

      // left
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

      // bottom
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},

      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)}
  };

  std::vector<ColoredVertex> vertex_vector = std::vector(std::begin(vertices), std::end(vertices));
  std::vector<unsigned int> index_vector;
  index_vector.reserve(vertex_vector.size());
  for (int i = 0; i < vertex_vector.size(); ++i) {
    index_vector.push_back(i);
  }

  ColoredMesh square = ColoredMesh(vertex_vector, index_vector);

  const double camera_offset = -20.0 / 3.0;

  while (!glfwWindowShouldClose(window)) {
    glm::vec4 camera_position = glm::vec4(10.0f * cos(glfwGetTime()), 0, 15.0f * sin(glfwGetTime()), 1);
    glm::mat4 camera_model = glm::mat4(1.0f);
    camera_model = glm::rotate(camera_model, 45.f, glm::vec3(1.0, 1.0, 0.0));
    camera_model = glm::translate(camera_model, glm::vec3(camera_offset, camera_offset, camera_offset));
    camera.MoveTo(glm::vec3(camera_model * camera_position));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    if (width != windowWidth || height != windowHeight) {
      windowWidth = width;
      windowHeight = height;
      shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.setMat4("view", camera.GetViewMatrix());
    shader.setVec3("viewPos", camera.Position);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, 45.f, glm::vec3(0.0, 0.0, 1.0));
//    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    shader.setMat4("model", model);
    square.Draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

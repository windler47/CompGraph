#define GL_SILENCE_DEPRECATION // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "helpers.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "GlObject.hpp"



int main() {
  int windowWidth = 640;
  int windowHeight = 480;
  GLFWwindow *window = prepareWindow(windowWidth, windowHeight,"Honor");
  loadGl();

  // configure gl
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Camera camera = Camera(glm::vec3(20.0f, 20.0f, 20.0f));
  Shader shader("shaders/color_vertex.glsl", "shaders/color_fragment.glsl");
  shader.Use();
  shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));

  shader.setVec3("light.direction", 1.0f, 1.0f, 1.0f);
  shader.setVec3("light.ambient", 0.05f, 0.05f, 0.05f);
  shader.setVec3("light.diffuse", 0.2f, 0.2f, 0.2f);
  shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };
  std::vector<unsigned int> index_vector = std::vector(std::begin(indices), std::end(indices));

  ColoredVertex vertices[] = {
      {.Position = glm::vec3(0.5f,  0.5f,  0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(0.5f,  -0.5f,  0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-0.5f,  -0.5f,  0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-0.5f,  0.5f,  0.0f), .Color = glm::vec3(1.0f, 1.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
  };
  std::vector<ColoredVertex> vertex_vector = std::vector(std::begin(vertices), std::end(vertices));

  ColoredMesh square = ColoredMesh(vertex_vector, index_vector);

  const float radius = 10.0f;
  while (!glfwWindowShouldClose(window)) {
//    float camX = sin(glfwGetTime()) * radius;
//    float camZ = cos(glfwGetTime()) * radius;
//    camera.MoveTo(glm::vec3(camX, 0, camZ));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    if (width != windowWidth || height != windowHeight){
      windowWidth = width;
      windowHeight = height;
      shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.setMat4("view", camera.GetViewMatrix());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,  0.0f,  0.0f));
//    model = glm::rotate(model, 45.f, glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    shader.setMat4("model", model);
    shader.setVec3("viewPos", camera.Position);

    square.Draw(shader);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

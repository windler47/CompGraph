#define GL_SILENCE_DEPRECATION // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "helpers.hpp"
#include "Shader.hpp"
#include "Camera.hpp"



int main() {
  uint32_t windowWidth = 640;
  uint32_t windowHeight = 480;
  GLFWwindow *window = prepareWindow(windowHeight, windowHeight, "Honor");
  loadGl();

  // configure gl
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Camera camera = Camera(glm::vec3(20, 20, 20));
  Shader theShader("shaders/color_vertex.glsl", "shaders/color_fragment.glsl");
  theShader.setMat4("projection", camera.GetProjectionMatrix(windowWidth, windowHeight));

  float vertices[] = {     //mormal           //color
      0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // верхняя правая
      0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // нижняя правая
      -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // нижняя левая
      -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f  // верхняя левая
  };

  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };

  //begin strange
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    if (width != windowWidth or height != windowHeight){
      theShader.setMat4("projection", camera.GetProjectionMatrix(float(width), float(height)));
      windowWidth = width;
      windowHeight = height;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    theShader.Use();
    theShader.setMat4("view", camera.GetViewMatrix());
    theShader.setVec3("light.direction", 1.0f, 1.0f, 1.0f);
    theShader.setVec3("viewPos", camera.Position);

    // свойства света
    theShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
    theShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    theShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


    glm::mat4 model = glm::mat4(1.0f);
    theShader.setMat4("model", model);
    // begin strange
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

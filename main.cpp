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
  Shader shader("shaders/simple_vertex.glsl", "shaders/simple_fragment.glsl");

//  float vertices[] = {
//      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
//      0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
//      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
//      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f
//  };

  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };
  std::vector<unsigned int> index_vector = std::vector(std::begin(indices), std::end(indices));

  ColoredVertex vertices[] = {
      {.Position = glm::vec3(0.5f,  0.5f,  0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(0.5f,  -0.5f,  0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f)},
      {.Position = glm::vec3(-0.5f,  -0.5f,  0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f)},
      {.Position = glm::vec3(-0.5f,  0.5f,  0.0f), .Color = glm::vec3(1.0f, 1.0f, 0.0f)},
  };
  std::vector<ColoredVertex> vertex_vector = std::vector(std::begin(vertices), std::end(vertices));

  ColoredObject square = ColoredObject(vertex_vector, index_vector);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

//    if (width != windowWidth or height != windowHeight){
//      shader.setMat4("projection", camera.GetProjectionMatrix((float) width, (float) height));
//      windowWidth = width;
//      windowHeight = height;
//    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();

    shader.setMat4("view", camera.GetViewMatrix());
    shader.setMat4("projection", camera.GetProjectionMatrix((float)width, (float)height));

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(0.0f,  0.0f,  0.0f));
    model = glm::rotate(model, 45.f, glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", model);

    square.Draw(shader);
//    glBindVertexArray(VAO); // поскольку у нас есть только один VАО, нет необходимости связывать его каждый раз, но мы сделаем это, чтобы все было немного более организованно
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    //glDrawArrays(GL_TRIANGLES, 0, 6);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

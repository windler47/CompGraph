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

  float vertices[] = {
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f
  };

  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };

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

  glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,  3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после мы можем спокойно отвязать
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // помните: не отвязывайте EBO, пока VАО активен, поскольку связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // После этого вы можете отменить привязку VАО, чтобы другие вызовы VАО случайно не изменили этот VAO, но это редко происходит.
  // Изменение других значений VAO требует вызова glBindVertexArray в любом случае, поэтому мы обычно не снимаем привязку VAO (или VBO), когда это непосредственно не требуется.
  glBindVertexArray(0);

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  std::cout << "-----BEGIN VIEW-----" << std::endl;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << view[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "-----END-----" << std::endl;

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
    glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    shader.setMat4("projection", camera.GetProjectionMatrix((float)width, (float)height));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,  0.0f,  0.0f));
    model = glm::rotate(model, 45.f, glm::vec3(0.0, 0.0, 1.0));

    shader.setMat4("model", model);


    glBindVertexArray(VAO); // поскольку у нас есть только один VАО, нет необходимости связывать его каждый раз, но мы сделаем это, чтобы все было немного более организованно
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

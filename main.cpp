#define GL_SILENCE_DEPRECATION // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <string>
#include "helpers.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "GlObject.hpp"

int main(int argc, char *argv[]) {
  unsigned int lab_number = 0;
  if (argc < 2){
    std::cerr << "Set lab number";
    exit(EXIT_FAILURE);
  } {
    std::string arg = argv[1];
    try {
      std::size_t pos;
      lab_number = std::stoi(arg, &pos);
      if (pos < arg.size()) {
        std::cerr << "Trailing characters after number: " << arg << '\n';
      }
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg << '\n';
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg << '\n';
    }
    if (lab_number == 0) {
      std::cerr << "Lab number parse failed";
      exit(EXIT_FAILURE);
    }
  }

  int windowWidth = 800;
  int windowHeight = 600;
  GLFWwindow *window = prepareWindow(windowWidth, windowHeight, "Maksimov");
  loadGl();
  // configure gl
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 3, 1,
      1, 4, 2,
      1, 3, 4
  };
  ColoredVertex vertices[] = {
      {.Position = glm::vec3(5.0f,  5.0f,  0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(0.0f,  5.0f,  0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-5.0f,  5.0f,  0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(2.0f,  0.0f,  0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-2.0f,  0.0f,  0.0f), .Color = glm::vec3(0.0f, 1.0f, 1.0f), .Normal = glm::vec3(0, 0, 1)},
  };

  Camera camera = Camera(glm::vec3(20.0f, 20.0f, 20.0f));
  Shader shader("shaders/color_vertex.glsl", "shaders/color_fragment.glsl");
  shader.Use();
  shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));
  shader.setVec3("light.direction", -1.0f, -1.0f, -1.0f);
  shader.setFloat("light.ambient", 0.05f);
  shader.setFloat("light.diffuse", 0.7f);
  shader.setFloat("light.specular", 1.0f);

  std::vector<ColoredVertex> vertex_vector;
  std::vector<unsigned int> index_vector;
  vertex_vector = std::vector(std::begin(vertices), std::end(vertices));
  index_vector = std::vector(std::begin(indices), std::end(indices));

  std::vector<ColoredVertex> two_sided_vertex_vector(vertex_vector);
  auto two_sided_index_vector(index_vector);
  for (int i = 0; i < vertex_vector.size(); ++i) {
    auto mirror_vertex = ColoredVertex {.Position = vertices[i].Position, .Color = vertices[i].Color, .Normal = - vertices[i].Normal };
    two_sided_vertex_vector.push_back(mirror_vertex);
  }
  for (unsigned int i : index_vector) {
    two_sided_index_vector.push_back(i+5);
  }
  ColoredMesh figure = ColoredMesh(two_sided_vertex_vector, two_sided_index_vector);


  while (!glfwWindowShouldClose(window)) {

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
    model = glm::rotate(model,(float) (glfwGetTime() * 4.0f), glm::vec3(1.0f, 1.0f, .0f));
    shader.setMat4("model", model);
    figure.Draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
//
//  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

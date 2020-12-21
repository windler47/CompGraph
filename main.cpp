#define GL_SILENCE_DEPRECATION // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include "helpers.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "GlObject.hpp"

#include <stb_image.h>
#include "lab_work_3.hpp"


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
  int windowWidth = 640;
  int windowHeight = 480;
  GLFWwindow *window = prepareWindow(windowWidth, windowHeight, "Honor");
  loadGl();
  // configure gl
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Camera camera = Camera(glm::vec3(0.0f, 10.0f, 15.0f));
  Shader shader("shaders/texture_vertex.glsl", "shaders/texture_fragment.glsl");
  shader.Use();
  shader.setMat4("projection", camera.GetProjectionMatrix((float) windowWidth, (float) windowHeight));
  shader.setVec3("light.direction", 1.0f, 1.0f, 1.0f);
  shader.setFloat("light.ambient", 0.1f);
  shader.setFloat("light.diffuse", 0.7f);
  shader.setFloat("light.specular", 0.9f);
  shader.setInt("texture", 0);

  std::vector<unsigned int> index_vector;
  std::vector<TexturedVertex> vertex_vector = std::vector(std::begin(LabThird::vertices), std::end(LabThird::vertices));;

  index_vector.reserve(vertex_vector.size());
  for (int i = 0; i < vertex_vector.size(); ++i) {
    index_vector.push_back(i);
  }
  unsigned int texture = load_texture("wooden_container.jpg");
  TexturedMesh figure = TexturedMesh(vertex_vector, index_vector, texture);

  while (!glfwWindowShouldClose(window)) {
    double t = glfwGetTime();
    double ellipse_x = 7.0f * cos(t);
    double ellipse_y = 12.0f * sin(t);
    double z = -ellipse_x - ellipse_y - 20;
    glm::vec3 camera_coords = glm::vec3(ellipse_x, ellipse_y, z);
    camera.MoveTo(camera_coords);

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
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    shader.setMat4("model", model);
    figure.Draw(shader);

    if (lab_number == 4){
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(1.5f, 1.5f, 2.0f));
      shader.setMat4("model", model);
      figure.Draw(shader);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // cleanup: освобождаем все ресурсы, как только они выполнили свое предназначение
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

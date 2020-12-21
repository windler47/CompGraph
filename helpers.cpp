#define GL_SILENCE_DEPRECATION  // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include "helpers.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>


struct Vertex
{
  glm::vec3 position;
  glm::vec4 color;
};

GLFWwindow* prepareWindow(uint32_t width, uint32_t height, const std::string& title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    exit(EXIT_FAILURE);
  } else
    std::cout << "GLFW init success" << std::endl;
  // GL version
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwSetErrorCallback(error_callback);

  GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    std::cerr << "Failed to create window or OpenGL context" << std::endl;
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSwapInterval(1); // enable vsync
  return window;
}

void loadGl() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    glfwTerminate();
    std::cerr << "Failed to initialize GLAD" << std::endl;
    exit(EXIT_FAILURE);
  }
}

//void bindVertexData(const std::vector<Vertex> &verticies)
//{
//  // OpenGL должен получить байтовые смещения полей относительно структуры VertexP2C4.
//  const void *colorOffset = reinterpret_cast<void *>(offsetof(Vertex, color));
//  const void *positionOffset = reinterpret_cast<void *>(offsetof(Vertex, position));
//  const size_t size = sizeof(Vertex);
//
//  // Привязываем атрибут i_color к данным в вершинном буфере.
//  const int colorLocation = glGetAttribLocation(m_program, "i_color");
//  glEnableVertexAttribArray(colorLocation);
//  glVertexAttribPointer(colorLocation, glm::vec4().length(), GL_FLOAT, GL_FALSE, stride, colorOffset);
//
//  // Привязываем атрибут i_position к данным в вершинном буфере.
//  const int posLocation = glGetAttribLocation(m_program, "i_position");
//  glEnableVertexAttribArray(posLocation);
//  glVertexAttribPointer(posLocation, glm::vec2().length(), GL_FLOAT, GL_FALSE, stride, posOffset);
//
//  // Загружаем данные в вершинный буфер.
//  glBufferData(GL_ARRAY_BUFFER, stride * verticies.size(), verticies.data(), GL_STATIC_DRAW);
//}

void print_gl_context_info()
{
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    std::cout << "Renderer:" << renderer << std::endl;
    std::cout << "OpenGL version supported:" << version << std::endl;
}



void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %d %s\n", error, description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else
        std::cout << "Key: " << key << " action: "<< action << " scancode: " << scancode << " mods: " << mods << std::endl;
}
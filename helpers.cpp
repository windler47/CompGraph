//
// Created by Aleksandr Maksimov on 17.12.2020.
//
#define GL_SILENCE_DEPRECATION  // We know that Apple don't like OpenGL API since macOS 10.14 but still want to use it
#define GLFW_INCLUDE_NONE

#include "helpers.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

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

unsigned int load_texture(const std::string& filename) {
  int width, height, nrChannels;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
  if (!data) {
    std::cout << "Failed to load texture" << std::endl;
    exit(EXIT_FAILURE);
  }
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
//  stbi_image_free(data);
  return texture;
}
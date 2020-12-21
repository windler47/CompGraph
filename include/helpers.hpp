#define GLFW_INCLUDE_NONE

#ifndef COMPUTERGRAPHICSNEW_HELPERS_HPP
#define COMPUTERGRAPHICSNEW_HELPERS_HPP

#include <string>
#include <GLFW/glfw3.h>

void loadGl();
GLFWwindow* prepareWindow(uint32_t width, uint32_t height, const std::string& title);

void print_gl_context_info();
void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int load_texture(const std::string& filename);

#endif //COMPUTERGRAPHICSNEW_HELPERS_HPP

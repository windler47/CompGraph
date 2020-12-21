#ifndef COMPUTERGRAPHICSNEW__LAB_WORK_1_HPP_
#define COMPUTERGRAPHICSNEW__LAB_WORK_1_HPP_
#include "GlObject.hpp"
namespace LabFirst{
  unsigned int indices[] = {  // помните, что мы начинаем с 0!
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };
  ColoredVertex vertices[] = {
      {.Position = glm::vec3(2.0f,  2.0f,  0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(2.0f,  -2.0f,  0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-2.0f,  -2.0f,  0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0, 0, 1)},
      {.Position = glm::vec3(-2.0f,  2.0f,  0.0f), .Color = glm::vec3(1.0f, 1.0f, 0.0f), .Normal = glm::vec3(0, 0, 1)}
  };
}
#endif //COMPUTERGRAPHICSNEW__LAB_WORK_1_HPP_
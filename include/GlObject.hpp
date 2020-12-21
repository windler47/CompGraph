//
// Created by Aleksandr Maksimov on 19.12.2020.
//

#ifndef COMPUTERGRAPHICSNEW__GLOBJECT_HPP_
#define COMPUTERGRAPHICSNEW__GLOBJECT_HPP_

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct ColoredVertex {
  glm::vec3 Position;
  glm::vec3 Color;
  glm::vec3 Normal;
};

class ColoredMesh {
 public:
  std::vector<ColoredVertex>  vertices;
  std::vector<unsigned int>   indices;

  ColoredMesh(std::vector<ColoredVertex> vertices, std::vector<unsigned int> indices);

  // Рендеринг mesh-а
  void Draw(Shader& shader);

 private:
  // Данные для рендеринга
  unsigned int VBO, VAO, EBO;
  // Инициализируем все буферные объекты/массивы
  void SetUp();
};

#endif //COMPUTERGRAPHICSNEW__GLOBJECT_HPP_

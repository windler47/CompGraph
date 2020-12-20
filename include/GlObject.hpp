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
};

struct TexturedVertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TextureCoordinate;
};


//struct Texture {
//  unsigned int id;
//  std::string type;
//  std::string path;
//};

class ColoredObject {
 public:
  std::vector<ColoredVertex>  vertices;
  std::vector<unsigned int>   indices;

  ColoredObject(std::vector<ColoredVertex> vertices, std::vector<unsigned int> indices);

  // Рендеринг mesh-а
  void Draw(Shader& shader);

 private:
  // Данные для рендеринга
  unsigned int VBO, VAO, EBO;
  // Инициализируем все буферные объекты/массивы
  void SetUp();
};

#endif //COMPUTERGRAPHICSNEW__GLOBJECT_HPP_

//
// Created by Aleksandr Maksimov on 19.12.2020.
//

#ifndef COMPUTERGRAPHICSNEW__GLOBJECT_HPP_
#define COMPUTERGRAPHICSNEW__GLOBJECT_HPP_

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct Vertex {

  // Позиция
  glm::vec3 Position;

  // Нормаль
  glm::vec3 Normal;

  // Текстурные координаты
  glm::vec2 TexCoords;

};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
 public:
  // Данные mesh-а
  std::vector<Vertex>       vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture>      textures;

  // Конструктор
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

  // Рендеринг mesh-а
  void Draw(Shader& shader);

 private:
  // Данные для рендеринга
  unsigned int VBO, VAO, EBO;

  // Инициализируем все буферные объекты/массивы
  void setupMesh();
};

#endif //COMPUTERGRAPHICSNEW__GLOBJECT_HPP_

//
// Created by Aleksandr Maksimov on 19.12.2020.
//

#ifndef COMPUTERGRAPHICSNEW__CAMERA_HPP_
#define COMPUTERGRAPHICSNEW__CAMERA_HPP_

#include <glm/glm.hpp>


// Абстрактный класс камеры, который обрабатывает входные данные и вычисляет соответствующие Эйлеровы углы, векторы и матрицы для использования в OpenGL
class Camera
{
 public:
  glm::vec3 Position;
  glm::vec3 Target;
  glm::vec3 Up;
  float Fov;  //Field of View
  float minVisibleDistance = 0.1f;
  float maxVisibleDistance = 100.0f;

  explicit Camera(const glm::vec3 &position, const glm::vec3 &target = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f), uint32_t fov = 45.0f);

  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix(float width, float height);
  void MoveTo(const glm::vec3 &position);

};
#endif //COMPUTERGRAPHICSNEW__CAMERA_HPP_

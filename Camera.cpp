#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, uint32_t fov) {
  Position = position;
  Target = target;
  Up = up;
  Fov = fov;
}
glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(Position, Target, Up);
}
glm::mat4 Camera::GetProjectionMatrix(float width, float height) {
  return glm::perspective(Fov, width/height, minVisibleDistance, maxVisibleDistance);
}
void Camera::MoveTo(const glm::vec3 &position) {
  Position = position;
}



//
// Created by Aleksandr Maksimov on 21.12.2020.
//

#ifndef COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_2_HPP_
#define COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_2_HPP_
namespace LabSecond {
  ColoredVertex vertices[] = {
      // rear
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

      // front
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

      // right
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

      // top
      {.Position = glm::vec3(2.0f, 2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
      {.Position = glm::vec3(3.0f, 3.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 0.0f), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

      // left
      {.Position = glm::vec3(-1.0f, 3.0f, 5.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, 2.0f, 0.0f), .Color = glm::vec3(0.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

      // bottom
      {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},

      {.Position = glm::vec3(2.0f, -2.0f, 0.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .Color = glm::vec3(1.0f, 0.0f, 1.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
      {.Position = glm::vec3(3.0f, -1.0f, 5.0f), .Color = glm::vec3(0.0f, 1.0f, 0.0f), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)}
  };
}
#endif //COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_2_HPP_

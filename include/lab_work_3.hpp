#ifndef COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_3_HPP_
#define COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_3_HPP_
#include "GlObject.hpp"
namespace LabThird {
 TexturedVertex vertices[] = {
    // rear
    {.Position = glm::vec3(2.0f, 2.0f, 0.0f),   .TextureCoords=glm::vec2(1.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(2.0f, -2.0f, 0.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

    {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .TextureCoords=glm::vec2(0.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(2.0f, -2.0f, 0.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(0.0f, 0.0f, -1.0f)},

    // front
    {.Position = glm::vec3(3.0f, 3.0f, 5.0f),   .TextureCoords=glm::vec2(1.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
    {.Position = glm::vec3(3.0f, -1.0f, 5.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
    {.Position = glm::vec3(-1.0f, 3.0f, 5.0f),  .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

    {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .TextureCoords=glm::vec2(0.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
    {.Position = glm::vec3(3.0f, -1.0f, 5.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},
    {.Position = glm::vec3(-1.0f, 3.0f, 5.0f),  .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(1.0f, 0.0f, 0.0f)},

    // right
    {.Position = glm::vec3(2.0f, 2.0f, 0.0f),   .TextureCoords=glm::vec2(1.0f, 1.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(2.0f, -2.0f, 0.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(3.0f, 3.0f, 5.0f),   .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

    {.Position = glm::vec3(3.0f, -1.0f, 5.0f),  .TextureCoords=glm::vec2(0.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(2.0f, -2.0f, 0.0f),  .TextureCoords=glm::vec2(1.0f, 0.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},
    {.Position = glm::vec3(3.0f, 3.0f, 5.0f),   .TextureCoords=glm::vec2(0.0f, 1.0f), .Normal = glm::vec3(5.0f, 0.0f, -1.0f)},

    // top
    {.Position = glm::vec3(2.0f, 2.0f, 0.0f),   .TextureCoords=glm::vec2(1.0, 1.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
    {.Position = glm::vec3(3.0f, 3.0f, 5.0f),   .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

    {.Position = glm::vec3(-1.0f, 3.0f, 5.0f),  .TextureCoords=glm::vec2(0.0, 0.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},
    {.Position = glm::vec3(3.0f, 3.0f, 5.0f),   .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(0.0f, 5.0f, -1.0f)},

    // left
    {.Position = glm::vec3(-1.0f, 3.0f, 5.0f),  .TextureCoords=glm::vec2(1.0, 1.0), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
    {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

    {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .TextureCoords=glm::vec2(0.0, 0.0), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
    {.Position = glm::vec3(-2.0f, 2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(-5.0f, 5.0f, 1.0f)},
    {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(-5.0f, 0.0f, 1.0f)},

    // bottom
    {.Position = glm::vec3(-1.0f, -1.0f, 5.0f), .TextureCoords=glm::vec2(1.0, 1.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
    {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
    {.Position = glm::vec3(3.0f, -1.0f, 5.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},

    {.Position = glm::vec3(2.0f, -2.0f, 0.0f),  .TextureCoords=glm::vec2(0.0, 0.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
    {.Position = glm::vec3(-2.0f, -2.0f, 0.0f), .TextureCoords=glm::vec2(1.0, 0.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)},
    {.Position = glm::vec3(3.0f, -1.0f, 5.0f),  .TextureCoords=glm::vec2(0.0, 1.0), .Normal = glm::vec3(0.0f, -5.0f, 1.0f)}
};
}
#endif //COMPUTERGRAPHICSNEW_INCLUDE_LAB_WORK_3_HPP_

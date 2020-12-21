#include "GlObject.hpp"

#include <utility>

ColoredMesh::ColoredMesh(std::vector<ColoredVertex> vertices, std::vector<unsigned int> indices) {
  this->vertices = std::move(vertices);
  this->indices = std::move(indices);
  SetUp();
}

void ColoredMesh::SetUp() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // fill vertex buffer
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ColoredVertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  // fill index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), (void*)nullptr);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,  3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), (void*)(offsetof(ColoredVertex, Color)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,  3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), (void*)(offsetof(ColoredVertex, Normal)));
  // вызов glVertexAttribPointer зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после мы можем спокойно отвязать
//  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  // помните: не отвязывайте EBO, пока VАО активен, поскольку связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void ColoredMesh::Draw(Shader &shader) {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

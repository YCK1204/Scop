#include "Mesh.hpp"
#include "Graphics_Include.hpp"

Mesh::Mesh(const float *_positions, int32 _vertexCount) : m_vao(0), m_vbo(0), m_vertexCount(_vertexCount) {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertexCount * 3 * sizeof(float), _positions, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
}

void Mesh::Draw() const {
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

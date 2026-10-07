#include "Mesh.hpp"
#include "Graphics_Include.hpp"

Mesh::Mesh(const float *_vertices, int32 _vertexCount, const std::vector<int32> &_attributeSizes)
    : m_vao(0), m_vbo(0), m_vertexCount(_vertexCount) {
  int32 floatsPerVertex = 0;
  for (int32 size : _attributeSizes) {
    floatsPerVertex += size;
  }

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertexCount * floatsPerVertex * sizeof(float), _vertices, GL_STATIC_DRAW);

  int32 offset = 0;
  for (uint32 index = 0; index < _attributeSizes.size(); index++) {
    glVertexAttribPointer(index, _attributeSizes[index], GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void *)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
    offset += _attributeSizes[index];
  }

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

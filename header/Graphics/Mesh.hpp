#pragma once

#include "Define.hpp"

class Mesh {
private:
  uint32 m_vao;
  uint32 m_vbo;
  int32 m_vertexCount;

private:
  Mesh();

public:
  /**
   * @brief 정점 위치 배열로 VAO, VBO를 만든다.
   * @param _positions 정점 위치 배열. 정점 하나당 float 3개 (x, y, z)
   * @param _vertexCount 정점 개수
   */
  Mesh(const float *_positions, int32 _vertexCount);
  /**
   * @brief VAO, VBO를 삭제한다. GL 컨텍스트가 살아 있는 동안 소멸되어야 한다
   */
  ~Mesh();
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;

public:
  /**
   * @brief VAO를 바인딩하고 삼각형으로 그린다. 쓸 프로그램은 호출 전에 Use 해둬야함
   */
  void Draw() const;
};

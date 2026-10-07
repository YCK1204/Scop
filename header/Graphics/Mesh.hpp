#pragma once

#include "Define.hpp"
#include <vector>

class Mesh {
private:
  uint32 m_vao;
  uint32 m_vbo;
  int32 m_vertexCount;

private:
  Mesh();

public:
  /**
   * @brief 정점 배열로 VAO, VBO를 만든다.
   * @param _vertices 정점 배열. 정점 하나의 속성들이 순서대로 붙어 있는 float 배열
   * @param _vertexCount 정점 개수
   * @param _attributeSizes 속성별 float 개수. 순서가 쉐이더의 layout (location = N)이 된다.
   * 예) 위치 3개 + 색 3개면 {3, 3}
   */
  Mesh(const float *_vertices, int32 _vertexCount, const std::vector<int32> &_attributeSizes);
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

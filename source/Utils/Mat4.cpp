#include "Utils/Mat4.hpp"
#include <cmath>

Mat4::Mat4() {
  m_matrices[0].x = 1;
  m_matrices[1].y = 1;
  m_matrices[2].z = 1;
  m_matrices[3].w = 1;
}

Mat4::Mat4(const Mat4 &_other) {
  *this = _other;
}

Mat4 &Mat4::operator=(const Mat4 &_other) {
  if (this != &_other) {
    m_matrices[0] = _other.m_matrices[0];
    m_matrices[1] = _other.m_matrices[1];
    m_matrices[2] = _other.m_matrices[2];
    m_matrices[3] = _other.m_matrices[3];
  }
  return *this;
}

Mat4 Mat4::operator*(const Mat4 &_other) const {
  Mat4 mat4(*this);

  mat4 *= _other;
  return mat4;
}

Mat4 &Mat4::operator*=(const Mat4 &_other) {
  Mat4 mat4(*this);

  for (int i = 0; i < 4; i++) {
    float x = mat4.m_matrices[i].x * _other.m_matrices[0].x + mat4.m_matrices[i].y * _other.m_matrices[1].x + mat4.m_matrices[i].z * _other.m_matrices[2].x + mat4.m_matrices[i].w * _other.m_matrices[3].x;
    float y = mat4.m_matrices[i].x * _other.m_matrices[0].y + mat4.m_matrices[i].y * _other.m_matrices[1].y + mat4.m_matrices[i].z * _other.m_matrices[2].y + mat4.m_matrices[i].w * _other.m_matrices[3].y;
    float z = mat4.m_matrices[i].x * _other.m_matrices[0].z + mat4.m_matrices[i].y * _other.m_matrices[1].z + mat4.m_matrices[i].z * _other.m_matrices[2].z + mat4.m_matrices[i].w * _other.m_matrices[3].z;
    float w = mat4.m_matrices[i].x * _other.m_matrices[0].w + mat4.m_matrices[i].y * _other.m_matrices[1].w + mat4.m_matrices[i].z * _other.m_matrices[2].w + mat4.m_matrices[i].w * _other.m_matrices[3].w;

    mat4.m_matrices[i] = Vec4(x, y, z, w);
  }

  *this = mat4;
  return *this;
}

Vec4 &Mat4::operator[](const int &_i) { return m_matrices[_i]; }

Mat4 Mat4::Translate(float _x, float _y, float _z) {
  Mat4 mat4;

  mat4.m_matrices[0].w = _x;
  mat4.m_matrices[1].w = _y;
  mat4.m_matrices[2].w = _z;
  return mat4;
}

Mat4 Mat4::Translate(Vec3 _vec3) { return Translate(_vec3.x, _vec3.y, _vec3.z); }

Mat4 Mat4::Scale(float _x, float _y, float _z) {
  Mat4 mat4;

  mat4.m_matrices[0].x = _x;
  mat4.m_matrices[1].y = _y;
  mat4.m_matrices[2].z = _z;
  return mat4;
}

Mat4 Mat4::Scale(Vec3 _vec3) { return Scale(_vec3.x, _vec3.y, _vec3.z); }

Mat4 Mat4::RotateX(float _v) {
  Mat4 mat4;
  float c = std::cos(_v);
  float s = std::sin(_v);

  mat4.m_matrices[1].y = c;
  mat4.m_matrices[1].z = -s;
  mat4.m_matrices[2].y = s;
  mat4.m_matrices[2].z = c;
  return mat4;
}

Mat4 Mat4::RotateY(float _v) {
  Mat4 mat4;
  float c = std::cos(_v);
  float s = std::sin(_v);

  mat4.m_matrices[0].x = c;
  mat4.m_matrices[0].z = s;
  mat4.m_matrices[2].x = -s;
  mat4.m_matrices[2].z = c;
  return mat4;
}

Mat4 Mat4::RotateZ(float _v) {
  Mat4 mat4;
  float c = std::cos(_v);
  float s = std::sin(_v);

  mat4.m_matrices[0].x = c;
  mat4.m_matrices[0].y = -s;
  mat4.m_matrices[1].x = s;
  mat4.m_matrices[1].y = c;
  return mat4;
}

Mat4 Mat4::Rotate(Vec3 _vec3) { return RotateZ(_vec3.z) * RotateY(_vec3.y) * RotateX(_vec3.x); }

const float *Mat4::data() const { return &m_matrices[0].x; }

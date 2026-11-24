#pragma once

#include "Utils/Vec3.hpp"
#include "Vec4.hpp"

struct Mat4 {
private:
  Vec4 m_matrices[4];

public:
  Mat4();
  Mat4(const Mat4 &_other);
  Mat4 &operator=(const Mat4 &_other);
  Mat4 operator*(const Mat4 &_other) const;
  Mat4 &operator*=(const Mat4 &_other);
  Vec4 &operator[](const int &_i);
  const float *data() const;

public:
  static Mat4 Translate(float _x, float _y, float _z);
  static Mat4 Translate(Vec3 _vec3);
  static Mat4 Scale(float _x, float _y, float _z);
  static Mat4 Scale(Vec3 _vec3);
  static Mat4 RotateX(float _v);
  static Mat4 RotateY(float _v);
  static Mat4 RotateZ(float _v);
  static Mat4 Rotate(Vec3 _vec3);
};
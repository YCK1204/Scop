#pragma once

struct Vec4 {
public:
  float x;
  float y;
  float z;
  float w;
  Vec4();
  Vec4(const Vec4& _other);
  Vec4(float _v);
  Vec4(float _x, float _y, float _z, float _w);
  Vec4 operator + (const Vec4 &_other);
  Vec4 operator - (const Vec4 &_other);
  Vec4 operator * (const Vec4 &_other);
  Vec4 operator / (const Vec4 &_other);
  Vec4 &operator += (const Vec4 & _other);
  Vec4 &operator -= (const Vec4 & _other);
  Vec4 &operator *= (const Vec4 & _other);
  Vec4 &operator /= (const Vec4 & _other);
  Vec4 &operator = (const Vec4 & _other);
};
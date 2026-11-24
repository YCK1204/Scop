#include "Utils/Vec4.hpp"

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(const Vec4 &_other) {
  x = _other.x;
  y = _other.y;
  z = _other.z;
  w = _other.w;
}
Vec4::Vec4(float _v) : x(_v), y(_v), z(_v), w(_v) {}
Vec4::Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

Vec4 Vec4::operator+(const Vec4 &_other) {
  Vec4 vec4(*this);

  vec4 += _other;
  return vec4;
}

Vec4 Vec4::operator-(const Vec4 &_other) {
  Vec4 vec4(*this);

  vec4 -= _other;
  return vec4;
}

Vec4 Vec4::operator*(const Vec4 &_other) {
  Vec4 vec4(*this);

  vec4 *= _other;
  return vec4;
}

Vec4 Vec4::operator/(const Vec4 &_other) {
  Vec4 vec4(*this);

  vec4 /= _other;
  return vec4;
}

Vec4 &Vec4::operator-=(const Vec4 &_other) {
  x -= _other.x;
  y -= _other.y;
  z -= _other.z;
  w -= _other.w;
  return *this;
}

Vec4 &Vec4::operator+=(const Vec4 &_other) {
  x += _other.x;
  y += _other.y;
  z += _other.z;
  w += _other.w;
  return *this;
}

Vec4 &Vec4::operator*=(const Vec4 &_other) {
  x *= _other.x;
  y *= _other.y;
  z *= _other.z;
  w *= _other.w;
  return *this;
}

Vec4 &Vec4::operator/=(const Vec4 &_other) {
  x /= _other.x;
  y /= _other.y;
  z /= _other.z;
  w /= _other.w;
  return *this;
}

Vec4 &Vec4::operator=(const Vec4 &_other) {
  if (&_other != this) {
    x = _other.x;
    y = _other.y;
    z = _other.z;
    w = _other.w;
  }
  return *this;
}

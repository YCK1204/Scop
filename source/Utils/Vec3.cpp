#include "Utils/Vec3.hpp"

Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(const Vec3 &_other) { x = _other.x; y = _other.y; z = _other.z; }
Vec3::Vec3(float _v) : x(_v), y(_v), z(_v) {}
Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vec3 &Vec3::operator-=(const Vec3 &_other) {
  x -= _other.x;
  y -= _other.y;
  z -= _other.z;
  return *this;
}

Vec3 &Vec3::operator+=(const Vec3 &_other) {
  x += _other.x;
  y += _other.y;
  z += _other.z;
  return *this;
}

Vec3 &Vec3::operator*=(const Vec3 &_other) {
  x *= _other.x;
  y *= _other.y;
  z *= _other.z;
  return *this;
}

Vec3 &Vec3::operator/=(const Vec3 &_other) {
    x /= _other.x;
    y /= _other.y;
    z /= _other.z;
  return *this;
}

Vec3 &Vec3::operator=(const Vec3 &_other) {
  if (&_other != this) {
    x = _other.x;
    y = _other.y;
    z = _other.z;
  }
  return *this;
}
#include "Rotation.hpp"
#include "Vec3.hpp"

Rotation::Rotation() {}

// 회전은 나중에 개발
Vec3 Rotation::operator=(const Vec3 &_other) {
  m_rotation = _other;
  return m_rotation;
}
Vec3 Rotation::operator+=(const Vec3 &_other) {
  m_rotation += _other;
  return m_rotation;
}
Vec3 Rotation::operator-=(const Vec3 &_other) {
  m_rotation -= _other;
  return m_rotation;
}
Vec3 Rotation::operator*=(const Vec3 &_other) {
  m_rotation *= _other;
  return m_rotation;
}
Vec3 Rotation::operator/=(const Vec3 &_other) {
  m_rotation /= _other;
  return m_rotation;
}

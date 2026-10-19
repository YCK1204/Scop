#include "Object/Position.hpp"

Position::Position() {}

Vec3 Position::operator=(const Vec3 &_other) {
  m_position = _other;
  return Vec3(m_position);
}
Vec3 Position::operator+=(const Vec3 &_other) {
  m_position += _other;
  return Vec3(m_position);
}
Vec3 Position::operator-=(const Vec3 &_other) {
  m_position -= _other;
  return Vec3(m_position);
}
Vec3 Position::operator*=(const Vec3 &_other) {
  m_position *= _other;
  return Vec3(m_position);
}
Vec3 Position::operator/=(const Vec3 &_other) {
  m_position /= _other;
  return Vec3(m_position);
}

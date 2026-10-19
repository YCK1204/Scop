#include "Object/Scale.hpp"

Scale::Scale() {
  m_scale = Vec3(1);
}

Vec3 Scale::operator=(const Vec3 &_other) {
  m_scale = _other;
  return Vec3(m_scale);
}
Vec3 Scale::operator+=(const Vec3 &_other) {
  m_scale += _other;
  return Vec3(m_scale);
}
Vec3 Scale::operator-=(const Vec3 &_other) {
  m_scale -= _other;
  return Vec3(m_scale);
}
Vec3 Scale::operator*=(const Vec3 &_other) {
  m_scale *= _other;
  return Vec3(m_scale);
}
Vec3 Scale::operator/=(const Vec3 &_other) {
  m_scale /= _other;
  return Vec3(m_scale);
}

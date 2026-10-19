#pragma once

#include "Utils/Vec3.hpp"
struct Rotation {

private:
  Vec3 m_rotation;

public:
  Rotation();
  Rotation(const Rotation &_other) = delete;
  Vec3 operator=(const Vec3 &_other);
  Vec3 operator+=(const Vec3 &_other);
  Vec3 operator-=(const Vec3 &_other);
  Vec3 operator*=(const Vec3 &_other);
  Vec3 operator/=(const Vec3 &_other);
  friend class Transform;
};
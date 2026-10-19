#pragma once

#include "Utils/Vec3.hpp"
struct Position {
private:
  Vec3 m_position;

public:
    Position();
    Position(const Position& _other) = delete;
    Vec3 operator = (const Vec3& _other);
    Vec3 operator += (const Vec3& _other);
    Vec3 operator -= (const Vec3& _other);
    Vec3 operator *= (const Vec3& _other);
    Vec3 operator /= (const Vec3& _other);
    friend class Transform;
};
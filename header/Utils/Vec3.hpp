#pragma once

struct Vec3 {
public:
  float x;
  float y;
  float z;
  Vec3();
  Vec3(const Vec3& _other);
  Vec3(float _v);
  Vec3(float _x, float _y, float _z);
  Vec3 &operator += (const Vec3 & _other);
  Vec3 &operator -= (const Vec3 & _other);
  Vec3 &operator *= (const Vec3 & _other);
  Vec3 &operator /= (const Vec3 & _other);
  Vec3 &operator = (const Vec3 & _other);
};
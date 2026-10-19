#pragma once

#include "Utils/Vec3.hpp"

class Transform;

struct Scale
{
private:
    Vec3 m_scale;
public:
    Scale();
    Scale(const Scale& _other) = delete;
    Vec3 operator = (const Vec3& _other);
    Vec3 operator += (const Vec3& _other);
    Vec3 operator -= (const Vec3& _other);
    Vec3 operator *= (const Vec3& _other);
    Vec3 operator /= (const Vec3& _other);
    friend class Transform;
};
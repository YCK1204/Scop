#include "Object/Transform.hpp"

Transform::Transform() {}
Vec3 Transform::GetScale() const { return m_scale.m_scale; }
void Transform::SetScale(const Vec3 &_vec3) { m_scale = _vec3; }
Vec3 Transform::GetPosition() const { return m_position.m_position; }
void Transform::SetPosition(const Vec3 &_vec3) { m_position = _vec3; }
Vec3 Transform::GetRotation() const { return m_rotation.m_rotation; }
void Transform::SetRotation(const Vec3 &_vec3) { m_rotation = _vec3; }
Mat4 Transform::GetModelMatrix() const {
  return Mat4::Translate(GetPosition()) * Mat4::Rotate(GetRotation()) * Mat4::Scale(GetScale());
}
const std::string &Transform::GetName() const { return m_name; }
void Transform::SetName(std::string _name) { m_name = _name; }

#pragma once

#include "Position.hpp"
#include "Object/Rotation.hpp"
#include "Scale.hpp"
#include "Utils/Mat4.hpp"
#include <string>

class Transform {
private:
  Position m_position;
  Rotation m_rotation;
  Scale m_scale;
  std::string m_name;

  Transform(const Transform &);
  Transform &operator=(const Transform &);

public:
  Transform();
  Vec3 GetScale() const;
  void SetScale(const Vec3& _vec3);
  Vec3 GetPosition() const;
  void SetPosition(const Vec3& _vec3);
  Vec3 GetRotation() const;
  void SetRotation(const Vec3& _vec3);
  /**
   * @brief 위치, 회전, 스케일을 합친 모델 행렬. Translate * Rotate * Scale 순서라 정점에는 스케일 → 회전 → 이동 순으로 적용된다
   */
  Mat4 GetModelMatrix() const;
  const std::string& GetName() const;
  void SetName(std::string _name);
};
#pragma once

#include "Define.hpp"

enum class ShaderType : uint16 {
  SHADER_VERTEX = 0x8B31,
  SHADER_FRAGMENT = 0x8B30,
};

class Shader {
private:
  uint32 m_id;
  ShaderType m_type;
  Shader();

public:
  Shader(uint32 _id, ShaderType _type);
  /**
   * @brief 쉐이더 객체를 삭제한다. GL 컨텍스트가 살아 있는 동안 소멸되어야 한다
   */
  ~Shader();
  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

public:
  const uint32 &GetId() const;
  const ShaderType &GetType() const;
};
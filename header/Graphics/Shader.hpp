#pragma once

#include "Define.hpp"

enum class ShaderType : uint16 {
  SHADER_VERTEX = 0x8B31,
  SHDAER_FRAGMENT = 0x8B30,
};

class Shader {
private:
  uint32 m_id;
  ShaderType m_type;
  Shader();

public:
  Shader(uint32 _id, ShaderType _type);
  const uint32 &GetId() const;
  const ShaderType &GetType() const;
};
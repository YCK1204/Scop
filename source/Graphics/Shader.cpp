#include "Shader.hpp"

Shader::Shader(uint32 _id, ShaderType _type) : m_id(_id), m_type(_type) {}

const uint32 &Shader::GetId() const { return m_id; }

const ShaderType &Shader::GetType() const { return m_type; }

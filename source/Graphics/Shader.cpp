#include "Shader.hpp"
#include "Graphics_Include.hpp"

Shader::Shader(uint32 _id, ShaderType _type) : m_id(_id), m_type(_type) {}

Shader::~Shader() { glDeleteShader(m_id); }

const uint32 &Shader::GetId() const { return m_id; }

const ShaderType &Shader::GetType() const { return m_type; }
void Shader::Compile(std::string &_src) {
  const char *str = _src.c_str();
  glShaderSource(m_id, 1, &str, NULL);
  glCompileShader(m_id);
  m_isCompiled = (GetIv(GL_COMPILE_STATUS) == GL_TRUE);
}
const bool &Shader::IsCompiled() const { return m_isCompiled; }

int32 Shader::GetIv(int32 _pname) const {
  int32 value;
  glGetShaderiv(m_id, _pname, &value);
  return value;
}

std::string Shader::GetInfoLog() const {
  int32 length = GetIv(GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetShaderInfoLog(m_id, length, &written, &log[0]);
  log.resize(written);
  return log;
}

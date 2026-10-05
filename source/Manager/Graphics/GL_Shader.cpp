#include "GL_Shader.hpp"

bool GL_Shader::Create(uint32 _type, int32 _count, const char **_source, const int32 *_length, Out uint32 &_id) const {
  _id = glCreateShader(_type);
  if (_id == 0) {
    return false;
  }

  glShaderSource(_id, _count, _source, _length);
  glCompileShader(_id);
  return GetShaderiv(_id, GL_COMPILE_STATUS) == GL_TRUE;
}

bool GL_Shader::CreateVertexShader(int32 _count, const char **_source, const int32 *_length, Out uint32 &_id) const {
  return Create(GL_VERTEX_SHADER, _count, _source, _length, _id);
}

bool GL_Shader::CreateFragmentShader(int32 _count, const char **_source, const int32 *_length, Out uint32 &_id) const {
  return Create(GL_FRAGMENT_SHADER, _count, _source, _length, _id);
}

int32 GL_Shader::GetShaderiv(uint32 _shaderId, uint32 _pname) const {
  int32 value = 0;

  glGetShaderiv(_shaderId, _pname, &value);
  return value;
}

std::string GL_Shader::GetShaderInfoLog(uint32 _shaderId) const {
  // 끝의 '\0'까지 포함한 길이
  int32 length = GetShaderiv(_shaderId, GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetShaderInfoLog(_shaderId, length, &written, &log[0]);
  log.resize(written);
  return log;
}

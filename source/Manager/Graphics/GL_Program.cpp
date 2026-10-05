#include "GL_Program.hpp"

uint32 GL_Program::CreateProgram() const { return glCreateProgram(); }

void GL_Program::AttachShader(uint32 _programId, uint32 _shaderId) const { glAttachShader(_programId, _shaderId); }

void GL_Program::LinkProgram(uint32 _programId) const { glLinkProgram(_programId); }

int32 GL_Program::GetProgramiv(uint32 _programId, uint32 _pname) const {
  int32 value = 0;

  glGetProgramiv(_programId, _pname, &value);
  return value;
}

std::string GL_Program::GetProgramInfoLog(uint32 _programId) const {
  // 끝의 '\0'까지 포함한 길이
  int32 length = GetProgramiv(_programId, GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetProgramInfoLog(_programId, length, &written, &log[0]);
  log.resize(written);
  return log;
}

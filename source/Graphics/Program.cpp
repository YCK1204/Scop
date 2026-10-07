#include "Program.hpp"
#include "Graphics_Include.hpp"

Program::Program(uint32 _id) : m_id(_id) {}
Program::~Program() { glDeleteProgram(m_id); }
const uint32 &Program::GetId() const { return m_id; }
int32 Program::Getiv(uint32 _pname) const {
  int32 value = 0;

  glGetProgramiv(m_id, _pname, &value);
  return value;
}
void Program::AttachShader(std::shared_ptr<Shader> _shader) const {
  if (_shader != nullptr)
    glAttachShader(m_id, _shader->GetId());
}
void Program::Link() const { glLinkProgram(m_id); }
std::string Program::GetInfoLog() const {
  int32 length = Getiv(GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetProgramInfoLog(m_id, length, &written, &log[0]);
  log.resize(written);
  return log;
}
void Program::Use() const { glUseProgram(m_id); }
int32 Program::GetUniformLocation(const std::string &_varName) const {
  return glGetUniformLocation(m_id, _varName.data());
}
void Program::SetUniform4f(int32 _location, float _x, float _y, float _z, float _w) const {
  Use();
  glUniform4f(_location, _x, _y, _z, _w);
}
void Program::SetUniform1f(int32 _location, float _value) const {
  Use();
  glUniform1f(_location, _value);
}

#include "Program.hpp"

Program::Program(uint32 _id) : m_id(_id) {}
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

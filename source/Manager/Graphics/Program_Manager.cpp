#include "Program_Manager.hpp"
#include "Graphics_Include.hpp"

std::shared_ptr<Program> Program_Manager::CreateProgram() {
  uint32 programId = glCreateProgram();

  std::shared_ptr<Program> program = nullptr;
  if (programId == 0) {
    return program;
  }

  program = std::make_shared<Program>(programId);
  m_programs[programId] = program;
  return program;
}
const std::shared_ptr<Program> Program_Manager::GetProgram(uint32 _id) const {
  std::map<uint32, std::shared_ptr<Program>>::const_iterator it = m_programs.find(_id);

  if (it == m_programs.end()) {
    return nullptr;
  }
  return it->second;
}
void Program_Manager::DeleteProgram(uint32 _id) { m_programs.erase(_id); }
void Program_Manager::DeleteProgram(std::shared_ptr<Program> _program) {
  if (_program != nullptr) {
    m_programs.erase(_program->GetId());
  }
}
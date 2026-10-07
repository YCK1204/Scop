#include "ProgramManager.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include <memory>

std::shared_ptr<Program> ProgramManager::CreateProgram() {
  uint32 programId = glCreateProgram();

  std::shared_ptr<Program> program = nullptr;
  if (programId == 0) {
    return program;
  }

  program = std::make_shared<Program>(programId);
  m_programs[programId] = program;
  return program;
}
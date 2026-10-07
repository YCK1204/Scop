#pragma once
#include "Define.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics_Include.hpp"
#include "Program.hpp"
#include <map>
#include <memory>
#include <string>

class ProgramManager {
private:
  std::map<uint32, std::shared_ptr<Program>> m_programs;

public:
  /**
   * @brief 빈 프로그램 객체를 만든다.
   * @return 프로그램 id. 실패하면 0
   */
  std::shared_ptr<Program> CreateProgram();
};

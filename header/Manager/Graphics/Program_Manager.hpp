#pragma once
#include "Define.hpp"
#include "Program.hpp"
#include "Singleton.hpp"
#include <map>
#include <memory>

class Program_Manager : public Singleton<Program_Manager> {
private:
  std::map<uint32, std::shared_ptr<Program>> m_programs;

public:
  /**
   * @brief 빈 프로그램 객체를 만든다.
   * @return 생성된 프로그램. 실패하면 nullptr
   */
  std::shared_ptr<Program> CreateProgram();
  /**
   * @brief CreateProgram으로 만든 프로그램 조회
   * @return 해당 id의 프로그램. 없으면 nullptr
   */
  const std::shared_ptr<Program> GetProgram(uint32 _id) const;
  /**
   * @brief 프로그램을 목록에서 뺀다.
   * GL 프로그램 객체는 마지막 shared_ptr이 사라질 때 Program 소멸자가 삭제한다
   */
  void DeleteProgram(uint32 _id);
  void DeleteProgram(std::shared_ptr<Program> _program);
};

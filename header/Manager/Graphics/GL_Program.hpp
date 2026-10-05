#pragma once
#include "Define.hpp"
#include "Graphics_Include.hpp"
#include <string>

class GL_Program {

public:
  /**
   * @brief 빈 프로그램 객체를 만든다.
   * @return 프로그램 id. 실패하면 0
   */
  uint32 CreateProgram() const;
  /**
   * @brief 컴파일된 쉐이더를 프로그램에 붙인다. LinkProgram 이전에 호출해야함
   */
  void AttachShader(uint32 _programId, uint32 _shaderId) const;
  /**
   * @brief 붙여둔 쉐이더들을 링크한다. 성공 여부는 GetProgramiv(GL_LINK_STATUS)로 확인
   */
  void LinkProgram(uint32 _programId) const;
  /**
   * @brief 프로그램 객체의 상태값 조회
   * @param _pname GL_LINK_STATUS, GL_INFO_LOG_LENGTH 등
   */
  int32 GetProgramiv(uint32 _programId, uint32 _pname) const;
  /**
   * @brief 프로그램 링크 로그. 로그가 없으면 빈 문자열
   */
  std::string GetProgramInfoLog(uint32 _programId) const;
};

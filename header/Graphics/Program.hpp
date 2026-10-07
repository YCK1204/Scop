#pragma once

#include "Define.hpp"
#include "Shader.hpp"
#include <memory>
#include <string>
#include "Graphics_Include.hpp"


class Program {
private:
  uint32 m_id;

private:
  Program();

public:
  Program(uint32 _id);
  const uint32 &GetId() const;
    /**
   * @brief 프로그램 객체의 상태값 조회
   * @param _pname GL_LINK_STATUS, GL_INFO_LOG_LENGTH 등
   */
  int32 Getiv(uint32 _pname) const;
public:
  /**
   * @brief 컴파일된 쉐이더를 프로그램에 붙인다. LinkProgram 이전에 호출해야함
   */
  void AttachShader(std::shared_ptr<Shader> _shader) const;
    /**
   * @brief 붙여둔 쉐이더들을 링크한다. 성공 여부는 GetProgramiv(GL_LINK_STATUS)로 확인
   */
  void Link() const;
    /**
   * @brief 프로그램 링크 로그. 로그가 없으면 빈 문자열
   */
  std::string GetInfoLog() const;
};
#pragma once

#include "Define.hpp"
#include "Shader.hpp"
#include <memory>
#include <string>

class Program {
private:
  uint32 m_id;

private:
  Program();

public:
  Program(uint32 _id);
  /**
   * @brief 프로그램 객체를 삭제한다. GL 컨텍스트가 살아 있는 동안 소멸되어야 한다
   */
  ~Program();
  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;

public:
  const uint32 &GetId() const;

public:
  /**
   * @brief 프로그램 객체의 상태값 조회
   * @param _pname GL_LINK_STATUS, GL_INFO_LOG_LENGTH 등
   */
  int32 Getiv(uint32 _pname) const;
  /**
   * @brief 컴파일된 쉐이더를 프로그램에 붙인다. Link 이전에 호출해야함
   * _shader가 nullptr이면 아무것도 하지 않는다
   */
  void AttachShader(std::shared_ptr<Shader> _shader) const;
  /**
   * @brief 붙여둔 쉐이더들을 링크한다. 성공 여부는 Getiv(GL_LINK_STATUS)로 확인
   */
  void Link() const;
  /**
   * @brief 프로그램 링크 로그. 로그가 없으면 빈 문자열
   */
  std::string GetInfoLog() const;

public:
  /**
   * @brief 이 프로그램을 현재 렌더링에 쓸 프로그램으로 지정한다.
   */
  void Use() const;
  /**
   * @brief 유니폼 변수의 위치 조회
   * @param _varName 쉐이더 안의 유니폼 변수 이름
   * @return 유니폼 위치. 없으면 -1
   */
  int32 GetUniformLocation(const std::string& _varName) const;
  /**
   * @brief vec4 유니폼 값을 넣는다. 유니폼은 현재 사용 중인 프로그램에 적용되므로 내부에서 Use를 먼저 호출한다.
   * @param _location GetUniformLocation으로 구한 위치
   */
  void SetUniform4f(int32 _location, float _x, float _y, float _z, float _w) const;
};
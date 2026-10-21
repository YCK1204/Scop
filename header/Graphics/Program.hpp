#pragma once

#include "Define.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Object;

class Program {
  friend class Object;

private:
  uint32 m_id;
  std::vector<std::weak_ptr<Object>> m_objects;
  std::map<std::string, int32> m_uniformLocations;

private:
  Program();

private:
  /**
   * @brief 이 프로그램으로 그릴 오브젝트를 등록한다. Object::SetProgram만 호출한다
   */
  void AddObject(const std::shared_ptr<Object> &_object);
  /**
   * @brief 등록된 오브젝트를 뺀다. 만료된 항목도 같이 정리한다. Object::SetProgram만 호출한다
   */
  void RemoveObject(const Object *_object);

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
  int32 GetUniformLocation(const std::string &_varName) const;
  /**
   * @brief vec4 유니폼 값을 넣는다. 유니폼은 현재 사용 중인 프로그램에 적용되므로 내부에서 Use를 먼저 호출한다.
   * @param _location GetUniformLocation으로 구한 위치
   */
  void SetUniform4f(int32 _location, float _x, float _y, float _z, float _w) const;
  /**
   * @brief float 유니폼 값을 넣는다. 내부에서 Use를 먼저 호출한다.
   * @param _location GetUniformLocation으로 구한 위치
   */
  void SetUniform1f(int32 _location, float _value) const;
  /**
   * @brief int 유니폼 값을 넣는다. sampler 유니폼에는 텍스처 유닛 번호를 넣는다. 내부에서 Use를 먼저 호출한다.
   * @param _location GetUniformLocation으로 구한 위치
   */
  void SetUniform1i(int32 _location, int32 _value) const;
  /**
   * @brief vec3 유니폼 값을 넣는다. 내부에서 Use를 먼저 호출한다.
   * @param _location GetUniformLocation으로 구한 위치
   */
  void SetUniform3f(int32 _location, float _x, float _y, float _z) const;

public:
  /**
   * @brief 쉐이더에 선언한 유니폼들의 위치를 조회해 이름별로 저장한다. Link 성공 이후 호출해야함.
   * 선언했지만 쉐이더에서 쓰지 않아 컴파일러가 지운 유니폼은 경고를 출력하고 저장하지 않는다
   * @param _uniforms ShaderSourceBuilder::GetUniforms의 결과. 버텍스, 프래그먼트 빌더 각각 호출하면 된다
   */
  void RegisterUniforms(const std::vector<UniformDecl> &_uniforms);
  /**
   * @brief RegisterUniforms로 등록된 이름인지 확인한다
   */
  bool HasUniform(const std::string &_name) const;
  /**
   * @brief 등록된 유니폼에 값을 넣는다. 값의 자료형에 맞는 SetUniform*을 호출한다
   * @return 등록되지 않은 이름이면 아무것도 하지 않고 false
   */
  bool SetUniform(const std::string &_name, const UniformValue &_value) const;

public:
  /**
   * @brief Use 한 번 뒤 등록된 오브젝트를 모두 그린다. 이미 사라진 오브젝트는 목록에서 정리한다. 매 프레임 호출
   */
  void DrawObjects();
};
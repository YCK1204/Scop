#pragma once
#include "Define.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics_Include.hpp"
#include "Singleton.hpp"
#include <map>
#include <memory>
#include <string>

class ShaderManager : public Singleton<ShaderManager> {
private:
  std::map<uint32, std::shared_ptr<Shader>> m_shaders;

private:
  /**
   * @brief _type 종류의 쉐이더 객체를 만들고 소스를 넣어 컴파일한다.
   */
  std::shared_ptr<Shader> Create(ShaderType _type, int32 _count, const char **_source, const int32 *_length);
  /**
   * @brief 쉐이더 객체의 상태값 조회
   * @param _pname GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH 등
   */
  int32 GetShaderiv(uint32 _id, uint32 _pname) const;
  /**
   * @brief 쉐이더 컴파일 로그. 로그가 없으면 빈 문자열
   */
public:
  /**
   * @brief 버텍스 쉐이더를 만들어 컴파일한다.
   * @param _count _source 배열의 문자열 개수
   * @param _source 쉐이더 소스 문자열 배열
   * @param _length 각 문자열의 길이 배열. NULL이면 문자열이 '\0'으로 끝난다고 본다
   * @param _id 생성된 쉐이더 id. 컴파일에 실패해도 채워지므로 GetShaderInfoLog에 쓸 수 있다
   * @return 컴파일에 성공하면 true, 실패하면 false
   */
  std::shared_ptr<Shader> CreateVertexShader(int32 _count, const char **_source, const int32 *_length) const;
  /**
   * @brief 프래그먼트 쉐이더를 만들어 컴파일한다. 인자는 CreateVertexShader와 같다.
   */
  std::shared_ptr<Shader> CreateFragmentShader(int32 _count, const char **_source, const int32 *_length) const;

  std::string GetShaderInfoLog(std::shared_ptr<Shader> _shader) const;

public:
  void DeleteShader(std::shared_ptr<Shader> _shader);
  void DeleteShader(uint32 _id);
};

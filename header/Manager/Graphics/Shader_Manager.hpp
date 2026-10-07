#pragma once
#include "Define.hpp"
#include "Shader.hpp"
#include "Singleton.hpp"
#include <map>
#include <memory>
#include <string>

class Shader_Manager : public Singleton<Shader_Manager> {
private:
  std::map<uint32, std::shared_ptr<Shader>> m_shaders;

private:
  /**
   * @brief _type 종류의 쉐이더 객체를 만들고 소스를 넣어 컴파일한다.
   * 컴파일에 실패하면 컴파일 로그를 출력하고 쉐이더 객체를 삭제한다.
   * @return 컴파일된 쉐이더. 생성이나 컴파일에 실패하면 nullptr
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
  std::string GetShaderInfoLog(uint32 _id) const;

public:
  /**
   * @brief 버텍스 쉐이더를 만들어 컴파일한다. 컴파일에 실패하면 컴파일 로그를 출력한다.
   * @param _count _source 배열의 문자열 개수
   * @param _source 쉐이더 소스 문자열 배열
   * @param _length 각 문자열의 길이 배열. NULL이면 문자열이 '\0'으로 끝난다고 본다
   * @return 컴파일된 쉐이더. 생성이나 컴파일에 실패하면 nullptr
   */
  std::shared_ptr<Shader> CreateVertexShader(int32 _count, const char **_source, const int32 *_length);
  /**
   * @brief 프래그먼트 쉐이더를 만들어 컴파일한다. 인자는 CreateVertexShader와 같다.
   */
  std::shared_ptr<Shader> CreateFragmentShader(int32 _count, const char **_source, const int32 *_length);

  /**
   * @brief 쉐이더 컴파일 로그. 로그가 없거나 _shader가 nullptr이면 빈 문자열
   */
  std::string GetShaderInfoLog(std::shared_ptr<Shader> _shader) const;

public:
  /**
   * @brief Create*Shader로 만든 쉐이더 조회
   * @return 해당 id의 쉐이더. 없으면 nullptr
   */
  const std::shared_ptr<Shader> GetShader(uint32 _id) const;
  /**
   * @brief 쉐이더를 목록에서 뺀다. 프로그램 링크가 끝난 뒤에 호출
   * GL 쉐이더 객체는 마지막 shared_ptr이 사라질 때 Shader 소멸자가 삭제한다
   */
  void DeleteShader(std::shared_ptr<Shader> _shader);
  void DeleteShader(uint32 _id);
};

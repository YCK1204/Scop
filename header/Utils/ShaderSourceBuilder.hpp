#pragma once

#include "Define.hpp"
#include "Uniform.hpp"
#include "Utils/ShaderSourceTemplate.hpp"
#include <string>
#include <vector>

class ShaderSourceBuilder {
private:
  std::string m_main;
  std::string m_header;
  std::vector<UniformDecl> m_uniforms;

public:
  std::string Build() const;

public:
  ShaderSourceBuilder &M_AddAddVar(std::string _key, std::string _val);
  ShaderSourceBuilder &M_AddSetVar(std::string _key, std::string _val);
  ShaderSourceBuilder &M_AddSubVar(std::string _key, std::string _val);
  ShaderSourceBuilder &M_AddMulVar(std::string _key, std::string _val);
  ShaderSourceBuilder &M_AddDivVar(std::string _key, std::string _val);
  ShaderSourceBuilder &M_AddModVar(std::string _key, std::string _val);

public:
  ShaderSourceBuilder &H_AddLayout(int32 _key1, std::string _type, std::string _key2);
  ShaderSourceBuilder &H_AddOut(std::string _type, std::string _key);
  ShaderSourceBuilder &H_AddIn(std::string _type, std::string _key);
  ShaderSourceBuilder &H_AddUniform(std::string _type, std::string _key);

public:
  /**
   * @brief H_AddUniform으로 선언한 유니폼 목록. 링크 후 Program::RegisterUniforms에 넘긴다
   */
  const std::vector<UniformDecl> &GetUniforms() const;
};

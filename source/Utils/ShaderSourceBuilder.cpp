#include "Utils/ShaderSourceBuilder.hpp"
#include "Utils/ShaderSourceTemplate.hpp"
#include "Utils/StringFormat.hpp"

std::string ShaderSourceBuilder::Build() const {
  std::string main = StringFormat::Format(ShaderSourceTemplate::Main::Base, m_main);

  return StringFormat::Format(
      ShaderSourceTemplate::Base,
      m_header,
      main);
}

#pragma region Main
ShaderSourceBuilder &ShaderSourceBuilder::M_AddAddVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::AddVar, _key, _val);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::M_AddSetVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::SetVar, _key, _val);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::M_AddSubVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::SubVar, _key, _val);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::M_AddMulVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::MulVar, _key, _val);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::M_AddDivVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::DivVar, _key, _val);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::M_AddModVar(std::string _key, std::string _val) {
  m_main += StringFormat::Format(ShaderSourceTemplate::Main::ModVar, _key, _val);
  return *this;
}
#pragma endregion

#pragma region Header
ShaderSourceBuilder &ShaderSourceBuilder::H_AddLayout(int32 _key1, std::string _type, std::string _key2) {
  m_header += StringFormat::Format(ShaderSourceTemplate::Header::Layout, _key1, _type, _key2);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::H_AddOut(std::string _type, std::string _key) {
  m_header += StringFormat::Format(ShaderSourceTemplate::Header::OutVar, _type, _key);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::H_AddIn(std::string _type, std::string _key) {
  m_header += StringFormat::Format(ShaderSourceTemplate::Header::InVar, _type, _key);
  return *this;
}
ShaderSourceBuilder &ShaderSourceBuilder::H_AddUniform(std::string _type, std::string _key) {
  m_header += StringFormat::Format(ShaderSourceTemplate::Header::UniformVar, _type, _key);
  m_uniforms.push_back({_type, _key});
  return *this;
}
#pragma endregion

const std::vector<UniformDecl> &ShaderSourceBuilder::GetUniforms() const { return m_uniforms; }

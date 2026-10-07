#include "Shader_Manager.hpp"
#include "Graphics_Include.hpp"
#include <iostream>

std::shared_ptr<Shader> Shader_Manager::Create(ShaderType _type, int32 _count, const char **_source, const int32 *_length) {
  uint32 shaderId;
  std::shared_ptr<Shader> shader = nullptr;
  shaderId = glCreateShader((uint32)_type);
  if (shaderId == 0) {
    return shader;
  }

  glShaderSource(shaderId, _count, _source, _length);
  glCompileShader(shaderId);
  if (GetShaderiv(shaderId, GL_COMPILE_STATUS) != GL_TRUE) {
    const char *typeName = _type == ShaderType::SHADER_VERTEX ? "VERTEX" : "FRAGMENT";

    std::cout << "ERROR::SHADER::" << typeName << "::COMPILATION_FAILED\n"
              << GetShaderInfoLog(shaderId) << std::endl;
    glDeleteShader(shaderId);
    return shader;
  }

  shader = std::make_shared<Shader>(shaderId, _type);
  m_shaders[shaderId] = shader;
  return shader;
}

std::shared_ptr<Shader> Shader_Manager::CreateVertexShader(int32 _count, const char **_source, const int32 *_length) {
  return Create(ShaderType::SHADER_VERTEX, _count, _source, _length);
}

std::shared_ptr<Shader> Shader_Manager::CreateFragmentShader(int32 _count, const char **_source, const int32 *_length) {
  return Create(ShaderType::SHADER_FRAGMENT, _count, _source, _length);
}

int32 Shader_Manager::GetShaderiv(uint32 _id, uint32 _pname) const {
  int32 value = 0;

  glGetShaderiv(_id, _pname, &value);
  return value;
}

std::string Shader_Manager::GetShaderInfoLog(std::shared_ptr<Shader> _shader) const {
  if (_shader == nullptr) {
    return std::string();
  }
  return GetShaderInfoLog(_shader->GetId());
}

std::string Shader_Manager::GetShaderInfoLog(uint32 _id) const {
  int32 length = GetShaderiv(_id, GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetShaderInfoLog(_id, length, &written, &log[0]);
  log.resize(written);
  return log;
}

const std::shared_ptr<Shader> Shader_Manager::GetShader(uint32 _id) const {
  std::map<uint32, std::shared_ptr<Shader>>::const_iterator it = m_shaders.find(_id);

  if (it == m_shaders.end()) {
    return nullptr;
  }
  return it->second;
}

void Shader_Manager::DeleteShader(std::shared_ptr<Shader> _shader) {
  if (_shader != nullptr) {
    m_shaders.erase(_shader->GetId());
  }
}

void Shader_Manager::DeleteShader(uint32 _id) { m_shaders.erase(_id); }

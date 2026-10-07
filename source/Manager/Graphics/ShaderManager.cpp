#include "ShaderManager.hpp"
#include "Graphics/Shader.hpp"
#include <memory>

std::shared_ptr<Shader> ShaderManager::Create(ShaderType _type, int32 _count, const char **_source, const int32 *_length) {
  uint32 shaderId;
  std::shared_ptr<Shader> shader = nullptr;
  shaderId = glCreateShader((uint32)_type);
  if (shaderId == 0) {
    return shader;
  }

  glShaderSource(shaderId, _count, _source, _length);
  glCompileShader(shaderId);
  if (GetShaderiv(shaderId, GL_COMPILE_STATUS) == GL_TRUE) {
    shader = std::make_shared<Shader>(shaderId, _type);
    m_shaders[shaderId] = shader;
  }

  return shader;
}

std::shared_ptr<Shader> ShaderManager::CreateVertexShader(int32 _count, const char **_source, const int32 *_length) const {
  return Create(ShaderType::SHADER_VERTEX, _count, _source, _length);
}

std::shared_ptr<Shader> ShaderManager::CreateFragmentShader(int32 _count, const char **_source, const int32 *_length) const {
  return Create(ShaderType::SHDAER_FRAGMENT, _count, _source, _length);
}

int32 ShaderManager::GetShaderiv(uint32 _id, uint32 _pname) const {
  int32 value = 0;

  glGetShaderiv(_id, _pname, &value);
  return value;
}

std::string ShaderManager::GetShaderInfoLog(std::shared_ptr<Shader> _shader) const {
  if (_shader == nullptr) {
    return std::string();
  }

  uint32 shaderId = _shader->GetId();
  int32 length = GetShaderiv(shaderId, GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetShaderInfoLog(shaderId, length, &written, &log[0]);
  log.resize(written);
  return log;
}

void ShaderManager::DeleteShader(std::shared_ptr<Shader> _shader) {
  if (_shader != nullptr) {
    glDeleteShader(_shader->GetId());
  }
}

void ShaderManager::DeleteShader(uint32 _id) {
  glDeleteShader(_id);
}

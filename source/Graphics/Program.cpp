#include "Program.hpp"
#include "Graphics_Include.hpp"
#include "Object/Object.hpp"
#include <iostream>
#include <type_traits>

Program::Program(uint32 _id) : m_id(_id) {}
Program::~Program() { glDeleteProgram(m_id); }
const uint32 &Program::GetId() const { return m_id; }
int32 Program::Getiv(uint32 _pname) const {
  int32 value = 0;

  glGetProgramiv(m_id, _pname, &value);
  return value;
}
void Program::AttachShader(std::shared_ptr<Shader> _shader) const {
  if (_shader != nullptr)
    glAttachShader(m_id, _shader->GetId());
}
void Program::Link() const { glLinkProgram(m_id); }
std::string Program::GetInfoLog() const {
  int32 length = Getiv(GL_INFO_LOG_LENGTH);
  if (length <= 0) {
    return std::string();
  }

  std::string log(length, '\0');
  int32 written = 0;

  glGetProgramInfoLog(m_id, length, &written, &log[0]);
  log.resize(written);
  return log;
}
void Program::Use() const { glUseProgram(m_id); }
int32 Program::GetUniformLocation(const std::string &_varName) const {
  return glGetUniformLocation(m_id, _varName.data());
}
void Program::SetUniform4f(int32 _location, float _x, float _y, float _z, float _w) const {
  Use();
  glUniform4f(_location, _x, _y, _z, _w);
}
void Program::SetUniform1f(int32 _location, float _value) const {
  Use();
  glUniform1f(_location, _value);
}
void Program::SetUniform1i(int32 _location, int32 _value) const {
  Use();
  glUniform1i(_location, _value);
}
void Program::SetUniform3f(int32 _location, float _x, float _y, float _z) const {
  Use();
  glUniform3f(_location, _x, _y, _z);
}

void Program::RegisterUniforms(const std::vector<UniformDecl> &_uniforms) {
  for (const UniformDecl &uniform : _uniforms) {
    int32 location = GetUniformLocation(uniform.name);
    if (location == -1) {
      std::cout << "WARNING::PROGRAM::UNIFORM_NOT_ACTIVE " << uniform.type << " " << uniform.name << std::endl;
      continue;
    }
    m_uniformLocations[uniform.name] = location;
  }
}

bool Program::HasUniform(const std::string &_name) const {
  return m_uniformLocations.find(_name) != m_uniformLocations.end();
}

/**
 * @brief std::visit으로 _value에 실제로 들어 있는 자료형을 꺼내, 자료형별 SetUniform*으로 나눠 보낸다
 */
bool Program::SetUniform(const std::string &_name, const UniformValue &_value) const {
  std::map<std::string, int32>::const_iterator it = m_uniformLocations.find(_name);
  if (it == m_uniformLocations.end()) {
    return false;
  }

  int32 location = it->second;
  std::visit(
      [this, location](const auto &_v) {
        using T = std::decay_t<decltype(_v)>;
        if constexpr (std::is_same_v<T, float>) {
          SetUniform1f(location, _v);
        } else if constexpr (std::is_same_v<T, int32>) {
          SetUniform1i(location, _v);
        } else {
          SetUniform3f(location, _v.x, _v.y, _v.z);
        }
      },
      _value);
  return true;
}

void Program::AddObject(const std::shared_ptr<Object> &_object) {
  if (_object != nullptr) {
    m_objects.push_back(_object);
  }
}

void Program::RemoveObject(const Object *_object) {
  for (std::vector<std::weak_ptr<Object>>::iterator it = m_objects.begin(); it != m_objects.end();) {
    std::shared_ptr<Object> object = it->lock();
    if (object == nullptr || object.get() == _object) {
      it = m_objects.erase(it);
    } else {
      ++it;
    }
  }
}

void Program::DrawObjects() {
  Use();
  for (std::vector<std::weak_ptr<Object>>::iterator it = m_objects.begin(); it != m_objects.end();) {
    std::shared_ptr<Object> object = it->lock();
    if (object == nullptr) {
      it = m_objects.erase(it);
      continue;
    }
    object->Draw();
    ++it;
  }
}

#include "Object/Object.hpp"
#include <iostream>
#include <string>

Object::Object() {}
Object::Object(const std::string _name) {
  SetName(_name);
}

const std::string &Object::GetName() const {
  return m_transform->GetName();
}

void Object::SetName(const std::string _name) { m_transform->SetName(_name); }

std::shared_ptr<Transform> Object::GetTransform() const {
  return m_transform;
}
void Object::SetProgram(const std::shared_ptr<Program> &_program) {
  std::shared_ptr<Program> old = m_program.lock();
  if (old == _program) {
    return;
  }
  if (old != nullptr) {
    old->RemoveObject(this);
  }
  m_program = _program;
  if (_program != nullptr) {
    _program->AddObject(shared_from_this());
  }
}

std::shared_ptr<Program> Object::GetProgram() const { return m_program.lock(); }

void Object::SetMesh(const std::shared_ptr<Mesh> _mesh) { m_mesh = _mesh; }

void Object::SetUniform(const std::string &_name, const UniformValue &_value) {
  std::shared_ptr<Program> program = m_program.lock();
  if (program != nullptr && !program->HasUniform(_name)) {
    std::cout << "WARNING::OBJECT::UNKNOWN_UNIFORM " << GetName() << " " << _name << std::endl;
  }
  m_uniformValues[_name] = _value;
}

void Object::Draw() const {
  std::shared_ptr<Program> program = m_program.lock();
  if (program != nullptr) {
    for (const auto &[name, value] : m_uniformValues) {
      program->SetUniform(name, value);
    }
  }
  if (m_mesh != nullptr) {
    m_mesh->Draw();
  }
}

#include "Object/Object.hpp"
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
void Object::SetProgram(const std::shared_ptr<Program> _program) { m_program = _program; }
void Object::SetMesh(const std::shared_ptr<Mesh> _mesh) { m_mesh = _mesh; }

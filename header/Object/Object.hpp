#pragma once

#include "Mesh.hpp"
#include "Object/Transform.hpp"
#include "Program.hpp"
#include <memory>
#include <string>
class Object {
private:
  std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
  Object(const Object &) = delete;
  Object &operator=(const Object&) = delete;
  std::shared_ptr<Program> m_program;
  std::shared_ptr<Mesh> m_mesh;

public:
  Object();
  Object(const std::string _name);
  const std::string &GetName() const;
  void SetName(const std::string _name);
  std::shared_ptr<Transform> GetTransform() const;
  void SetProgram(const std::shared_ptr<Program> _program);
  void SetMesh(const std::shared_ptr<Mesh> _mesh);
  
  friend class ObjectManager;
};
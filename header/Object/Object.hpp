#pragma once

#include "Mesh.hpp"
#include "Object/Transform.hpp"
#include "Program.hpp"
#include "Uniform.hpp"
#include <map>
#include <memory>
#include <string>
class Object : public std::enable_shared_from_this<Object> {
private:
  std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
  Object(const Object &) = delete;
  Object &operator=(const Object&) = delete;
  std::weak_ptr<Program> m_program;
  std::shared_ptr<Mesh> m_mesh;
  std::map<std::string, UniformValue> m_uniformValues;

public:
  Object();
  Object(const std::string _name);
  const std::string &GetName() const;
  void SetName(const std::string _name);
  std::shared_ptr<Transform> GetTransform() const;
  /**
   * @brief 이 오브젝트를 그릴 프로그램을 바꾼다. 이전 프로그램의 목록에서 빠지고 새 프로그램의 목록에 들어간다.
   * 프로그램은 참조만 하고 소유하지 않는다(소유는 Program_Manager).
   * shared_from_this를 쓰므로 오브젝트가 shared_ptr로 관리되고 있을 때만 호출해야 한다
   * @param _program 새 프로그램. nullptr이면 어떤 프로그램으로도 그려지지 않는다
   */
  void SetProgram(const std::shared_ptr<Program> &_program);
  /**
   * @brief 이 오브젝트를 그리는 프로그램. 프로그램이 없거나 이미 삭제됐으면 nullptr
   */
  std::shared_ptr<Program> GetProgram() const;
  void SetMesh(const std::shared_ptr<Mesh> _mesh);
  /**
   * @brief 이 오브젝트를 그릴 때 넣을 유니폼 값을 저장한다. 실제로 쉐이더에 들어가는 시점은 Draw.
   * 프로그램이 연결되어 있는데 그 프로그램에 없는 이름이면 경고를 출력한다(값은 저장한다)
   * @param _name 쉐이더에 선언한 유니폼 이름
   * @param _value 넣을 값. float, int32, Vec3
   */
  void SetUniform(const std::string &_name, const UniformValue &_value);
  /**
   * @brief 저장된 유니폼 값을 프로그램에 넣고 메쉬를 그린다. 프로그램 Use는 호출하는 쪽(Program::DrawObjects)이 해둬야 한다.
   * 같은 프로그램을 쓰는 오브젝트끼리 유니폼 값을 덮어쓰므로, 값은 그리기 직전에 넣는다
   */
  void Draw() const;
  
  friend class ObjectManager;
};
#include "ObjectManager.hpp"
#include "Object/Object.hpp"
#include <memory>

bool ObjectManager::Init() { return true; }

void ObjectManager::SetObject(std::shared_ptr<Object> _obj) {
  if (_obj) {
    m_objects[_obj->GetName()] = _obj;
  }
}
std::shared_ptr<Object> ObjectManager::GetObject(std::string _key) {
  std::map<std::string, std::shared_ptr<Object>>::const_iterator it = m_objects.find(_key);
  if (it == m_objects.end()) {
    return nullptr;
  }
  return it->second;
}
void ObjectManager::DeleteObject(std::string _key) { m_objects.erase(_key); }

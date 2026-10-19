#pragma once

#include "Object/Object.hpp"
#include "Singleton.hpp"
#include <map>
#include <memory>
#include <string>
class ObjectManager : public Singleton<ObjectManager> {
private:
    std::map<std::string, std::shared_ptr<Object>> m_objects;

public:
    void SetObject(std::shared_ptr<Object> _obj);
    std::shared_ptr<Object> GetObject(std::string _key);
    void DeleteObject(std::string _key);
};
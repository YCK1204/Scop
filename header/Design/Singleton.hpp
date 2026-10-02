#pragma once
#include <cstddef>

template <typename T>
class Singleton {
private:
  inline static T *m_instance = nullptr;

public:
  virtual ~Singleton() {}

public:
  static void DestroyInstance() {
    delete m_instance;
    m_instance = nullptr;
  }

  static T *GetInstance() {
    if (m_instance == nullptr) {
      m_instance = new T();
    }
    return m_instance;
  }
};
#pragma once
#include <cstddef>

template <typename T>
class Singleton {
private:
  inline static T *m_instance = nullptr;

public:
  virtual ~Singleton();

public:
  static void DestroyInstance();
  static T *GetInstance();
};

template <typename T>
Singleton<T>::~Singleton() {}

template <typename T>
void Singleton<T>::DestroyInstance() {
  delete m_instance;
  m_instance = nullptr;
}

template <typename T>
T *Singleton<T>::GetInstance() {
  if (m_instance == nullptr) {
    m_instance = new T();
  }
  return m_instance;
}

#pragma once

template <typename T>
class Singleton {
private:
  inline static T *m_instance = nullptr;

public:
  virtual ~Singleton();

public:
  static void DestroyInstance();
  static T *GetInstance();
  /**
   * @brief 매니저 초기화. Managers::TryInitialize가 인스턴스를 만든 직후 한 번 호출한다.
   * 할 일이 없는 매니저는 true만 반환하면 된다
   * @return 초기화에 성공하면 true
   */
  virtual bool Init() = 0;
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

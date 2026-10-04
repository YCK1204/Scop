#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief C# 제네릭처럼 사용되는 delegate class
 */
template <typename... Args>
class Event {
public:
  using Callback = void (*)(Args...);

private:
  std::vector<Callback> m_callbacks;

public:
  void operator+=(Callback _callback);
  void operator-=(Callback _callback);
  void operator()(Args... _args) const;
  void Invoke(Args... _args) const;
};

template <typename... Args>
void Event<Args...>::operator+=(Callback _callback) {
  m_callbacks.push_back(_callback);
}

template <typename... Args>
void Event<Args...>::operator-=(Callback _callback) {
  m_callbacks.erase(
      std::remove(m_callbacks.begin(), m_callbacks.end(), _callback),
      m_callbacks.end());
}

template <typename... Args>
void Event<Args...>::operator()(Args... _args) const {
  Invoke(_args...);
}

template <typename... Args>
void Event<Args...>::Invoke(Args... _args) const {
  std::vector<Callback> listeners = m_callbacks;

  for (Callback callback : listeners) {
    callback(_args...);
  }
}

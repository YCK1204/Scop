#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace StringFormat {
template <typename T>
std::string ToString(const T &_value) {
  std::ostringstream oss;
  oss << _value;
  return oss.str();
}

template <typename... Args>
std::string Format(const std::string &_src, const Args &..._args) {
  std::vector<std::string> values = {ToString(_args)...};
  std::string result = _src;
  std::size_t i = 0;
  std::string target;

  while (i < values.size()) {
    target = "{" + std::to_string(i) + "}";
    std::size_t targetPos = result.find(target);
    std::size_t targetStrLen = target.length();

    while (targetPos != std::string::npos) {
      result.erase(targetPos, targetStrLen);
      result.insert(targetPos, values[i]);

      targetPos += values[i].length();
      targetPos = result.find(target);
    }
    i++;
  }
  return result;
}
} // namespace StringFormat

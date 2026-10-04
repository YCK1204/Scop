#include "Input_Manager.hpp"

Input_Manager::Input_Manager() {}

std::map<Key, Event<>> &Input_Manager::GetCallbacks(Input_Type _type) {
  return m_callbacks[static_cast<uint8>(_type)];
}

void Input_Manager::Invoke(Input_Type _type, Key _key) {
  std::map<Key, Event<>> &callbacks = GetCallbacks(_type);
  auto it = callbacks.find(_key);

  if (it != callbacks.end()) {
    Event<> event = it->second;
    event();
  }
}

void Input_Manager::AddCallback(Input_Type _type, Key _key, Callback _callback) {
  GetCallbacks(_type)[_key] += _callback;
}

void Input_Manager::RemoveCallback(Input_Type _type, Key _key, Callback _callback) {
  std::map<Key, Event<>> &callbacks = GetCallbacks(_type);
  auto it = callbacks.find(_key);

  if (it != callbacks.end()) {
    it->second -= _callback;
  }
}

void Input_Manager::ClearCallbacks(Input_Type _type, Key _key) {
  GetCallbacks(_type).erase(_key);
}

void Input_Manager::OnKeyEvent(Input_Type _type, Key _key) {
  if (_type == Input_Type::INPUT_PRESS) {
    m_heldKeys.insert(_key);
  } else if (_type == Input_Type::INPUT_RELEASE) {
    m_heldKeys.erase(_key);
  }

  Invoke(_type, _key);
}

void Input_Manager::Update() {
  std::set<Key> heldKeys = m_heldKeys;

  for (Key key : heldKeys) {
    Invoke(Input_Type::INPUT_HOLD, key);
  }
}

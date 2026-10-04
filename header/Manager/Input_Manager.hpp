#pragma once
#include "Define.hpp"
#include "Event.hpp"
#include "Key.hpp"
#include "Singleton.hpp"
#include <map>
#include <set>

enum class Input_Type : uint8 {
  INPUT_HOLD,    // 누르고 있는 동안 매 프레임
  INPUT_PRESS,   // 누른 순간 한 번
  INPUT_RELEASE, // 뗀 순간 한 번
  INPUT_REPEAT,  // 누르고 있을 때 OS 키 반복 (글자 입력 같은 반복)
  INPUT_MAX
};

class Input_Manager : public Singleton<Input_Manager> {
  friend class Singleton<Input_Manager>;

public:
  using Callback = Event<>::Callback;

private:
  std::map<Key, Event<>> m_callbacks[static_cast<uint8>(Input_Type::INPUT_MAX)];
  std::set<Key> m_heldKeys;

private:
  Input_Manager();

private:
  std::map<Key, Event<>> &GetCallbacks(Input_Type _type);
  void Invoke(Input_Type _type, Key _key);

public:
  /**
   * @brief 키 입력 콜백 등록
   * @param _type 언제 호출할지 (HOLD / PRESS / RELEASE / REPEAT)
   * @param _key 키 코드 (Key::*)
   * @param _callback 인자와 반환값이 없는 함수
   */
  void AddCallback(Input_Type _type, Key _key, Callback _callback);
  /**
   * @brief AddCallback으로 등록한 콜백 해제
   */
  void RemoveCallback(Input_Type _type, Key _key, Callback _callback);
  /**
   * @brief 해당 종류, 해당 키에 등록된 콜백 전부 해제
   */
  void ClearCallbacks(Input_Type _type, Key _key);

public:
  /**
   * @brief 키 상태가 바뀌었을 때 호출. PRESS / RELEASE / REPEAT 콜백을 부르고 눌린 키 목록을 갱신한다.
   * GLF_Manager가 GLFW 키 콜백에서 호출한다.
   * @param _type INPUT_PRESS / INPUT_RELEASE / INPUT_REPEAT 중 하나
   * @param _key 키 코드
   */
  void OnKeyEvent(Input_Type _type, Key _key);
  /**
   * @brief 매 프레임 호출. 지금 눌려 있는 키들의 HOLD 콜백을 부른다.
   * GLF_Manager::HandleInput이 호출한다.
   */
  void Update();
};

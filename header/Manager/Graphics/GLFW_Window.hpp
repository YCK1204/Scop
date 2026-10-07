#pragma once
#include "Graphics_Include.hpp"

class GLFW_Window {

private:
  GLFWwindow *m_window = nullptr;

private:
  /**
   * @brief GLFW가 키 상태 변화 때 부르는 콜백. Input_Manager로 전달한다.
   */
  static void OnKey(GLFWwindow *, int _key, int, int _action, int);
  /**
   * @brief GLFW가 프레임버퍼 크기 변화 때 부르는 콜백. 뷰포트를 새 크기에 맞춘다.
   * 창 크기를 바꿀 때와 디스플레이 배율이 적용될 때 불린다.
   * @param _width 프레임버퍼 너비 (픽셀)
   * @param _height 프레임버퍼 높이 (픽셀)
   */
  static void OnFramebufferSize(GLFWwindow *, int _width, int _height);

public:
  /**
   * @brief 어떤 방식으로 OpenGL을 사용할지에 관한 명세 Hint
   * Graphics_Manager::Init 이후, Create 이전 호출해야함
   * hint와 value는 GLFW 문서의 Window hints 참고
   */
  void AddHint(int hint, int value) const;
  /**
   * @brief GLFW 창을 생성해 m_window에 저장하고 키 콜백과 프레임버퍼 크기 콜백을 등록한다.
   * @param width 창 너비 (픽셀)
   * @param height 창 높이 (픽셀)
   * @param title 창 제목
   * @param monitor 전체 화면으로 띄울 모니터. 창 모드면 NULL
   * @param share 컨텍스트 리소스를 공유할 창. 없으면 NULL
   * @return 창 생성에 성공하면 true, 실패하면 false. 실패 시 Graphics_Manager::Terminate는 호출자가 부른다
   */
  bool Create(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);

  void MakeContextCurrent() const;

  /**
   * @brief GLFW에 창을 닫으라는 명령이 내려졌는지 확인함
   * 명령이 내려진 경우엔 true, 그 외 false
   */
  bool ShouldClose() const;
  void SetShouldClose(bool _close);

  /**
   * @brief 키보드 입력이나 마우스 움직임 같은 이벤트 발생 확인, 창 상태 업데이트, 해당 함수들 호출
   */
  void PollEvents() const;
  /**
   * @brief 렌더링 반복에서 사용되는 컬러 버퍼를 교체하고 교체된 버퍼를 화면에 출력
   */
  void SwapBuffers() const;
};

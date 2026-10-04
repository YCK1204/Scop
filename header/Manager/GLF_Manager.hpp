#pragma once
#include "Define.hpp"
#include "Singleton.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <ostream>

class GLF_Manager : public Singleton<GLF_Manager> {

private:
  GLFWwindow *m_window = nullptr;

private:
  /**
   * @brief GLFW가 키 상태 변화 때 부르는 콜백. Input_Manager로 전달한다.
   */
  static void OnKey(GLFWwindow *, int _key, int, int _action, int);

  /**
   * @brief 키보드 입력이나 마우스 움직임 같은 이벤트 발생 확인, 창 상태 업데이트, 해당 함수들 호출
   */
  void PollEvents() const;
  /**
   * @brief 렌더링 반복에서 사용되는 컬러 버퍼를 교체하고 교체된 버퍼를 화면에 출력
   */
  void SwapBuffers() const;

  /**
   * @brief 키, 마우스 이벤트 관리. 매 프레임 Input_Manager::Update를 호출한다.
   */
  void HandleInput() const;

  /**
   * @brief GLFW에 창을 닫으라는 명령이 내려졌는지 확인함
   * 명령이 내려진 경우엔 true, 그 외 false
   */
  bool ShouldClose() const;

#pragma region 초기화 및 창 생성
public:
  /**
   * @brief 무조건 맨 처음 실행되어야할 초기화 함수
   * @return true 초기화 성공
   * @return false 초기화 실패
   */
  bool Init() const;
  /**
   * @brief 어떤 방식으로 OpenGL을 사용할지에 관한 명세 Hint
   * Init 이후, CreateWindow 이전 호출해야함
   * hint와 value는 glfw-window-hints.md 참고
   */
  void AddHint(int hint, int value) const;
  /**
   * @brief GLFW 창을 생성해 m_window에 저장한다. 실패하면 GLFW를 종료한다.
   * @param width 창 너비 (픽셀)
   * @param heigiht 창 높이 (픽셀)
   * @param title 창 제목
   * @param monitor 전체 화면으로 띄울 모니터. 창 모드면 NULL
   * @param share 컨텍스트 리소스를 공유할 창. 없으면 NULL
   * @return 창 생성에 성공하면 true, 실패하면 false
   */
  bool CreateWindow(int width, int heigiht, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
#pragma endregion

public:
  /**
   * @brief 렌더링 시작점과 영역 지정 함수
   * @param x 렌더링 시작점 x
   * @param y 렌더링 시작점 y
   * @param width 렌더링 영역 width
   * @param height 렌더링 영역 height
   */
  void Viewport(int x, int y, int width, int height) const {
    glViewport(x, y, width, height);
  }

public:
  void MakeContextCurrent() const;

  void Run() const;
  /**
   * @brief GLFW에 사용되던 모든 리소스 정리 및 삭제, 창 닫은 이후 시점에 호출
   */
  void Terminate() const;

  void SetWindowShouldClose(bool _close);
};

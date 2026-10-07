#pragma once
#include "GLFW_Window.hpp"
#include "Graphics_Include.hpp"
#include "Singleton.hpp"

class Graphics_Manager : public Singleton<Graphics_Manager> {

private:
  GLFW_Window m_window;

private:
  /**
   * @brief 키, 마우스 이벤트 관리. 매 프레임 Input_Manager::Update를 호출한다.
   */
  void HandleInput() const;

public:
  /**
   * @brief 무조건 맨 처음 실행되어야할 초기화 함수
   * @return true 초기화 성공
   * @return false 초기화 실패
   */
  bool Init() const;
  /**
   * @brief 매니저에 남은 메쉬, 쉐이더, 프로그램을 해제한 뒤 GLFW에 사용되던 모든 리소스 정리 및 삭제
   * 창 닫은 이후 시점에 호출
   */
  void Terminate() const;

public:
  /**
   * @brief 창 파트. 힌트, 창 생성, 컨텍스트, 닫힘 플래그는 여기로 접근한다.
   */
  GLFW_Window &GetWindow();

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
  /**
   * @brief Render_Manager를 준비하고 창이 닫힐 때까지 렌더링 루프를 돈다.
   * 준비에 실패하면 루프 없이 바로 반환한다.
   * 창 생성과 MakeContextCurrent 이후 호출해야함
   */
  void Run() const;
};

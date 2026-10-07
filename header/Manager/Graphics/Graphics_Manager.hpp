#pragma once
#include "Graphics_Include.hpp"
#include "Define.hpp"
#include "GL_Program.hpp"
#include "GLFW_Window.hpp"
#include "Singleton.hpp"
#include <iostream>
#include <map>
#include <ostream>

class Graphics_Manager : public Singleton<Graphics_Manager> {

private:
  GLFW_Window m_window;
  GL_Program m_program;

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
   * @brief GLFW에 사용되던 모든 리소스 정리 및 삭제, 창 닫은 이후 시점에 호출
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
  void Run() const;
};

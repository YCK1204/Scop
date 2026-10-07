#pragma once
#include "Define.hpp"
#include "Mesh.hpp"
#include "Program.hpp"
#include "Singleton.hpp"
#include <memory>

class Render_Manager : public Singleton<Render_Manager> {
private:
  std::shared_ptr<Program> m_program;
  std::unique_ptr<Mesh> m_mesh;
  int32 m_colorLocation = -1;

public:
  /**
   * @brief 쉐이더를 컴파일해 프로그램을 링크하고 그릴 메쉬를 만든다.
   * 창 생성과 MakeContextCurrent 이후 호출해야함
   * @return 준비에 성공하면 true. 쉐이더 컴파일이나 링크에 실패하면 false
   */
  bool Init();
  /**
   * @brief 화면을 지우고 한 프레임을 그린다. Init 성공 이후 매 프레임 호출
   */
  void Update() const;
};

#pragma once
#include "Define.hpp"
#include "Mesh.hpp"
#include "Program.hpp"
#include "Singleton.hpp"
#include <memory>
#include <vector>

/**
 * @brief 프로그램 하나와 그 프로그램으로 그릴 메쉬들의 묶음
 */
struct RenderBatch {
  std::shared_ptr<Program> program;
  std::vector<std::shared_ptr<Mesh>> meshes;
};

class Render_Manager : public Singleton<Render_Manager> {
private:
  std::vector<RenderBatch> m_batches;

public:
  /**
   * @brief 쉐이더를 컴파일해 프로그램을 링크하고, 그릴 메쉬를 만들어 AddMesh로 등록한다.
   * 창 생성과 MakeContextCurrent 이후 호출해야함
   * @return 준비에 성공하면 true. 쉐이더 컴파일이나 링크에 실패하면 false
   */
  bool Init();
  /**
   * @brief _program으로 그릴 메쉬를 추가한다. 같은 프로그램에 여러 번 호출하면 그 프로그램의 메쉬 목록에 쌓인다.
   * _program이나 _mesh가 nullptr이면 추가하지 않는다
   */
  void AddMesh(std::shared_ptr<Program> _program, std::shared_ptr<Mesh> _mesh);
  /**
   * @brief 화면을 지우고 프로그램별로 한 번 Use 한 뒤 그 프로그램의 메쉬를 모두 그린다. 매 프레임 호출
   */
  void Update() const;
};

#pragma once
#include "Define.hpp"
#include "Singleton.hpp"

class Render_Manager : public Singleton<Render_Manager> {
public:
  /**
   * @brief 할 일 없음. GL 준비는 GL 컨텍스트가 필요하므로 InitScene에서 한다
   */
  bool Init() override;
  /**
   * @brief 쉐이더를 컴파일해 프로그램을 링크하고, 메쉬를 가진 오브젝트를 만들어 ObjectManager에 등록한 뒤 그 프로그램에 연결한다.
   * 임시 조작용 키 콜백(B, WASD)도 여기서 등록한다.
   * 창 생성과 MakeContextCurrent 이후 호출해야함
   * @return 준비에 성공하면 true. 쉐이더 컴파일이나 링크에 실패하면 false
   */
  bool InitScene();
  /**
   * @brief 화면을 지우고 프로그램마다 DrawObjects를 호출한다(프로그램별 Use 한 번 + 연결된 오브젝트 전부 그리기). 매 프레임 호출
   * 임시: 프레임 간격(delta time)을 갱신하고, quad의 Transform으로 만든 모델 행렬을 Model 유니폼에 넣는다.
   * Transform은 B(모드 전환: NONE → POSITION → SCALE → ROTATION) + WASD 입력으로 바뀐다
   */
  void Update() const;
};

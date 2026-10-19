#pragma once
#include <string>
#include "Define.hpp"
#include "File_Manager.hpp"
#include "Graphics_Manager.hpp"
#include "Input_Manager.hpp"
#include "Log_Manager.hpp"
#include "ObjectManager.hpp"
#include "Program_Manager.hpp"
#include "Render_Manager.hpp"
#include "Shader_Manager.hpp"
#include "TextureManager.hpp"

class Managers {
private:
  Managers() = delete;

private:
  /**
   * @brief T 매니저의 인스턴스를 만들고 Init을 호출한다.
   * @param _name 실패 메시지에 쓸 매니저 이름
   * @param _errMessage 실패하면 원인이 담긴다
   * @return 인스턴스 생성과 Init이 모두 성공하면 true
   */
  template <typename T>
  static bool TryInitManager(const char *_name, Out std::string &_errMessage);

public:
  static bool TryInitialize(Out std::string &_errMessage);
  static void DestroyManagers();

public:
  static File_Manager *File();
  static Log_Manager *Log();
  static Graphics_Manager *Graphics();
  static Input_Manager *Input();
  static Shader_Manager *Shader();
  static Program_Manager *Program();
  static Render_Manager *Render();
  static TextureManager *Texture();
  static ObjectManager *Objects();
};

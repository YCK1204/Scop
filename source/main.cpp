#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include "Input_Manager.hpp"
#include "Managers.hpp"

int main() {
  std::string initMsg;
  if (!Managers::TryInitialize(initMsg))
  {
    std::cout << initMsg << std::endl;
    return 1;
  }

  Managers::GLF()->AddHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 주 버전 3.3의 첫 3
  Managers::GLF()->AddHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 버전의 숫자 3.3의 두 번째 3
  Managers::GLF()->AddHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Managers::Input()->AddCallback(Input_Type::INPUT_PRESS, Key::ESCAPE,
    [](){ Managers::GLF()->SetWindowShouldClose(true);}
  );

  bool success = Managers::GLF()->CreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (!success) {
    return -1;
  }
  Managers::GLF()->MakeContextCurrent();
  Managers::GLF()->Run();
  Managers::GLF()->Terminate();
  return 0;
}

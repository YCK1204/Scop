#include "GLF_Manager.hpp"
#include "Define.hpp"
#include "Input_Manager.hpp"
#include <GLFW/glfw3.h>

#pragma region 초기화 및 창 생성
bool GLF_Manager::Init() const { return glfwInit() == GLFW_TRUE; }

void GLF_Manager::AddHint(int hint, int value) const { glfwWindowHint(hint, value); }

bool GLF_Manager::CreateWindow(int width, int heigiht, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
  m_window = glfwCreateWindow(width, heigiht, title, monitor, share);

  if (m_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    Terminate();
    return false;
  }

  glfwSetKeyCallback(m_window, OnKey);
  return true;
}
#pragma endregion

void GLF_Manager::MakeContextCurrent() const { glfwMakeContextCurrent(m_window); }

bool GLF_Manager::ShouldClose() const { return glfwWindowShouldClose(m_window); }

void GLF_Manager::PollEvents() const { glfwPollEvents(); }

void GLF_Manager::Run() const {
  while (!ShouldClose()) {
    HandleInput();
    SwapBuffers();
    PollEvents();
  }
}

void GLF_Manager::Terminate() const { glfwTerminate(); }
void GLF_Manager::SetWindowShouldClose(bool _close) { glfwSetWindowShouldClose(m_window, _close); }

void GLF_Manager::SwapBuffers() const { glfwSwapBuffers(m_window); }

void GLF_Manager::HandleInput() const { Input_Manager::GetInstance()->Update(); }

void GLF_Manager::OnKey(GLFWwindow *, int _key, int, int _action, int) {
  if (_key < 0) {
    return;
  }

  Input_Type type;

  switch (_action) {
  case GLFW_PRESS:
    type = Input_Type::INPUT_PRESS;
    break;
  case GLFW_RELEASE:
    type = Input_Type::INPUT_RELEASE;
    break;
  case GLFW_REPEAT:
    type = Input_Type::INPUT_REPEAT;
    break;
  default:
    return;
  }

  Input_Manager::GetInstance()->OnKeyEvent(type, static_cast<Key>(_key));
}

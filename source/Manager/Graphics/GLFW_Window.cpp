#include "GLFW_Window.hpp"
#include "Input_Manager.hpp"
#include <iostream>

void GLFW_Window::AddHint(int hint, int value) const { glfwWindowHint(hint, value); }

bool GLFW_Window::Create(int width, int heigiht, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
  m_window = glfwCreateWindow(width, heigiht, title, monitor, share);

  if (m_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    return false;
  }

  glfwSetKeyCallback(m_window, OnKey);
  return true;
}

void GLFW_Window::MakeContextCurrent() const { glfwMakeContextCurrent(m_window); }

bool GLFW_Window::ShouldClose() const { return glfwWindowShouldClose(m_window); }

void GLFW_Window::SetShouldClose(bool _close) { glfwSetWindowShouldClose(m_window, _close); }

void GLFW_Window::PollEvents() const { glfwPollEvents(); }

void GLFW_Window::SwapBuffers() const { glfwSwapBuffers(m_window); }

void GLFW_Window::OnKey(GLFWwindow *, int _key, int, int _action, int) {
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

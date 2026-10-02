#include "GLF_Manager.hpp"

bool GLF_Manager::Init() const { return glfwInit() == GLFW_TRUE; }

void GLF_Manager::AddHint(int hint, int value) const { glfwWindowHint(hint, value); }

bool GLF_Manager::CreateWindow(int width, int heigiht, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
  m_window = glfwCreateWindow(width, heigiht, title, monitor, share);

  if (m_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    Terminate();
    return false;
  }
  return true;
}

void GLF_Manager::MakeContextCurrent() const { glfwMakeContextCurrent(m_window); }

bool GLF_Manager::ShouldClose() const { return glfwWindowShouldClose(m_window); }

void GLF_Manager::PollEvents() const { glfwPollEvents(); }

void GLF_Manager::Run() const {
  while (!ShouldClose()) {
    PollEvents();
  }
}

void GLF_Manager::Terminate() const { glfwTerminate(); }

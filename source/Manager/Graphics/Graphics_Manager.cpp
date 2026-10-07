#include "Graphics_Manager.hpp"
#include "Input_Manager.hpp"
#include "Managers.hpp"

bool Graphics_Manager::Init() const { return glfwInit() == GLFW_TRUE; }

void Graphics_Manager::Terminate() const {
  Render_Manager::DestroyInstance();
  Shader_Manager::DestroyInstance();
  Program_Manager::DestroyInstance();
  glfwTerminate();
}

GLFW_Window &Graphics_Manager::GetWindow() { return m_window; }

void Graphics_Manager::Run() const {
  if (!Managers::Render()->Init()) {
    return;
  }

  while (!m_window.ShouldClose()) {
    Managers::Render()->Update();
    HandleInput();
    m_window.SwapBuffers();
    m_window.PollEvents();
  }
}

void Graphics_Manager::HandleInput() const { Input_Manager::GetInstance()->Update(); }

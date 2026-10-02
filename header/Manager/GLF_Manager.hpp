#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include "Singleton.hpp"

class GLF_Manager : public Singleton<GLF_Manager> {

private:
  GLFWwindow* m_window = nullptr;

public:
  bool Init() const;
  void AddHint(int hint, int value) const;
  bool CreateWindow(int width, int heigiht, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
  void MakeContextCurrent() const;
  bool ShouldClose() const;
  void PollEvents() const;
  void Run() const;
  void Terminate() const;
};

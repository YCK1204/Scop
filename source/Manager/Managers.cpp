#include "Managers.hpp"

bool Managers::TryInitialize(Out std::string &_errMessage)
{
  const char *managerName = "File_Manager";

  try
  {
    File_Manager::GetInstance();

    managerName = "Log_Manager";
    Log_Manager::GetInstance();

    managerName = "Graphics_Manager";
    Graphics_Manager::GetInstance();

    managerName = "Input_Manager";
    Input_Manager::GetInstance();

    managerName = "Shader_Manager";
    Shader_Manager::GetInstance();

    managerName = "Program_Manager";
    Program_Manager::GetInstance();

    managerName = "Render_Manager";
    Render_Manager::GetInstance();
  }
  catch (const std::bad_alloc &)
  {
    _errMessage = std::string(managerName) + " Instance is not assigned";
    return false;
  }

  File()->SetPath("./");
  if (!Log()->Init("log.txt"))
  {
    _errMessage = "Failed to open log file";
    return false;
  }

  if (!Graphics()->Init())
  {
    _errMessage = "Failed to initialize GLFW";
    Log()->Log(Log_Level::LOG_CRITICAL, _errMessage.c_str());
    return false;
  }

  return true;
}
void Managers::DestroyManagers() 
{
  File_Manager::GetInstance()->DestroyInstance();
  Log_Manager::GetInstance()->DestroyInstance();
  Render_Manager::GetInstance()->DestroyInstance();
  Shader_Manager::GetInstance()->DestroyInstance();
  Program_Manager::GetInstance()->DestroyInstance();
  Graphics_Manager::GetInstance()->DestroyInstance();
  Input_Manager::GetInstance()->DestroyInstance();
}

File_Manager *Managers::File() { return File_Manager::GetInstance(); }

Log_Manager *Managers::Log() { return Log_Manager::GetInstance(); }

Graphics_Manager *Managers::Graphics() { return Graphics_Manager::GetInstance(); }

Input_Manager *Managers::Input() { return Input_Manager::GetInstance(); }

Shader_Manager *Managers::Shader() { return Shader_Manager::GetInstance(); }

Program_Manager *Managers::Program() { return Program_Manager::GetInstance(); }

Render_Manager *Managers::Render() { return Render_Manager::GetInstance(); }

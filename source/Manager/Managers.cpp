#include "Managers.hpp"
#include <new>

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

File_Manager *Managers::File() { return File_Manager::GetInstance(); }

Log_Manager *Managers::Log() { return Log_Manager::GetInstance(); }

Graphics_Manager *Managers::Graphics() { return Graphics_Manager::GetInstance(); }

Input_Manager *Managers::Input() { return Input_Manager::GetInstance(); }

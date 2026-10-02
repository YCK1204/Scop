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

    managerName = "GLF_Manager";
    GLF_Manager::GetInstance();
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

  if (!GLF()->Init())
  {
    _errMessage = "Failed to initialize GLFW";
    Log()->Log(Log_Level::LOG_CRITICAL, _errMessage.c_str());
    return false;
  }

  return true;
}

File_Manager *Managers::File() { return File_Manager::GetInstance(); }

Log_Manager *Managers::Log() { return Log_Manager::GetInstance(); }

GLF_Manager *Managers::GLF() { return GLF_Manager::GetInstance(); }

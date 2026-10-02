#pragma once
#include <string>
#include "Define.hpp"
#include "File_Manager.hpp"
#include "GLF_Manager.hpp"
#include "Log_Manager.hpp"

class Managers {
private:
  Managers() = delete;

public:
  static bool TryInitialize(Out std::string &_errMessage);

public:
  static File_Manager *File();
  static Log_Manager *Log();
  static GLF_Manager *GLF();
};

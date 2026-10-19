#include "Managers.hpp"
#include "ObjectManager.hpp"
#include "TextureManager.hpp"

template <typename T>
bool Managers::TryInitManager(const char *_name, Out std::string &_errMessage)
{
  try
  {
    if (T::GetInstance()->Init())
    {
      return true;
    }
    _errMessage = std::string(_name) + " Init failed";
  }
  catch (const std::bad_alloc &)
  {
    _errMessage = std::string(_name) + " Instance is not assigned";
  }
  return false;
}

/**
 * @brief 순서가 의미 있다. File_Manager가 기준 경로를 정해야 Log_Manager가 로그 파일을 열 수 있다
 */
bool Managers::TryInitialize(Out std::string &_errMessage)
{
  return TryInitManager<File_Manager>("File_Manager", _errMessage)
      && TryInitManager<Log_Manager>("Log_Manager", _errMessage)
      && TryInitManager<Graphics_Manager>("Graphics_Manager", _errMessage)
      && TryInitManager<Input_Manager>("Input_Manager", _errMessage)
      && TryInitManager<Shader_Manager>("Shader_Manager", _errMessage)
      && TryInitManager<Program_Manager>("Program_Manager", _errMessage)
      && TryInitManager<Render_Manager>("Render_Manager", _errMessage)
      && TryInitManager<TextureManager>("TextureManager", _errMessage)
      && TryInitManager<ObjectManager>("ObjectManager", _errMessage);
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
  ObjectManager::GetInstance()->DestroyInstance();
}

File_Manager *Managers::File() { return File_Manager::GetInstance(); }

Log_Manager *Managers::Log() { return Log_Manager::GetInstance(); }

Graphics_Manager *Managers::Graphics() { return Graphics_Manager::GetInstance(); }

Input_Manager *Managers::Input() { return Input_Manager::GetInstance(); }

Shader_Manager *Managers::Shader() { return Shader_Manager::GetInstance(); }

Program_Manager *Managers::Program() { return Program_Manager::GetInstance(); }

Render_Manager *Managers::Render() { return Render_Manager::GetInstance(); }

TextureManager *Managers::Texture() { return TextureManager::GetInstance(); }

ObjectManager *Managers::Objects() { return ObjectManager::GetInstance(); }

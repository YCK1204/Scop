#pragma once
#include "Define.hpp"
#include "Singleton.hpp"
#include <fstream>
#include <map>
#include <string>

class File_Manager : public Singleton<File_Manager> {
  friend class Singleton<File_Manager>;

private:
  std::map<std::string, std::string> m_Files;
  std::string m_basePath;

private:
  std::string GetFullPath(const std::string &_fileName) const;

private:
  File_Manager();

public:
  void SetPath(const std::string &_path);

public:
  bool HasFileStr(const std::string &_fileName) const;
  bool TryGetFileStr(const std::string &_fileName, Out const std::string *&_fileStr) const;
  bool ReadAndSetFileStr(const std::string &_fileName, std::ifstream &_file, bool _forceOverWrite = false);
  bool TryOpenFile(const std::string &_fileName, Out std::ifstream &_file) const;

public:
  bool TryOpenFile(const std::string &_fileName, Out std::ofstream &_file, std::ios_base::openmode _mode = std::ios_base::out) const;
};

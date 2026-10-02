#include "File_Manager.hpp"

File_Manager::File_Manager() {}

std::string File_Manager::GetFullPath(const std::string &_fileName) const {
  return m_basePath + _fileName;
}

void File_Manager::SetPath(const std::string &_path) {
  m_basePath = _path;
  if (!m_basePath.empty() && m_basePath.back() != '/') {
    m_basePath.append("/");
  }
}

bool File_Manager::HasFileStr(const std::string &_fileName) const {
  return m_Files.find(_fileName) != m_Files.end();
}

bool File_Manager::TryGetFileStr(const std::string &_fileName, Out const std::string *&_fileStr) const {
  std::map<std::string, std::string>::const_iterator it = m_Files.find(_fileName);
  if (it == m_Files.end()) {
    _fileStr = nullptr;
    return false;
  }
  _fileStr = &it->second;
  return true;
}

bool File_Manager::ReadAndSetFileStr(const std::string &_fileName, std::ifstream &_file, bool _forceOverWrite) {
  if (!HasFileStr(_fileName) || _forceOverWrite) {
    std::string fileStr;

    if (!_file.is_open()) {
      _file.open(GetFullPath(_fileName));
    }

    if (_file.fail()) {
      return false;
    }

    std::stringstream ss;
    ss << _file.rdbuf();
    _file.close();

    m_Files[_fileName] = ss.str();

    return true;
  }

  return false;
}

bool File_Manager::TryOpenFile(const std::string &_fileName, Out std::ifstream &_file) const {
  _file.open(GetFullPath(_fileName));

  return !_file.fail();
}

bool File_Manager::TryOpenFile(const std::string &_fileName, Out std::ofstream &_file,
                               std::ios_base::openmode _mode) const {
  _file.open(GetFullPath(_fileName), _mode);

  return !_file.fail();
}

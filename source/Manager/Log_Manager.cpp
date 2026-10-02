#include "Log_Manager.hpp"
#include <cstdlib>
#include "File_Manager.hpp"

const char* Log_Manager::GetLevelStr(Log_Level _level) const
{
    switch (_level)
    {
        case Log_Level::LOG_INIT:     return "INIT";
        case Log_Level::LOG_INFO:     return "INFO";
        case Log_Level::LOG_WARNING:  return "WARNING";
        case Log_Level::LOG_CRITICAL: return "CRITICAL";
    }
    return "UNKNOWN";
}

bool Log_Manager::Init(const std::string& _fileName)
{
    return File_Manager::GetInstance()->TryOpenFile(_fileName, m_logFile);
}

void Log_Manager::Log(Log_Level _level, const char* value)
{
    if (m_logFile.is_open())
    {
        m_logFile << "[" << GetLevelStr(_level) << "] " << value << std::endl;
    }

    if (_level == Log_Level::LOG_CRITICAL)
    {
        exit(1);
    }
}

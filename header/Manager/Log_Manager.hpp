#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "Singleton.hpp"


enum class Log_Level : uint8_t  {
    LOG_INIT,
    LOG_INFO,
    LOG_WARNING,
    LOG_CRITICAL
};

class Log_Manager  : public Singleton<Log_Manager> {
private:
    std::ofstream m_logFile;

private:
    const char* GetLevelStr(Log_Level _level) const;

public:
    bool Init(const std::string& _fileName);
    void Log(Log_Level _level, const char* value);
};

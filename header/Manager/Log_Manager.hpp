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
    /**
     * @brief File_Manager의 기준 경로 아래에 log.txt를 연다. File_Manager::Init 이후 호출해야함
     * @return 로그 파일을 열었으면 true
     */
    bool Init() override;
    void Log(Log_Level _level, const char* value);
};

#pragma once

#include <mutex>
#include <iostream>
#include <memory>

namespace crossmatch
{
    enum class Level
    {
        TRACE = 0,
        DEBUG = 1, 
        INFO = 2,
        WARNING = 3,
        ERROR = 4
    };

    class Log;
    extern std::unique_ptr<Log> log;

    class Log {
    public:
        Log();
        Log(const Level &level);

        void SetLevel(const Level &level);
        Level GetLevel() const;

        void trace(const std::string &msg...);
        void debug(const std::string &msg...);
        void info(const std::string &msg...);
        void warning(const std::string &msg...);
        void error(const std::string &msg...);

    private:
        void LogInternal(const Level &level, const std::string &msg, va_list args);
        std::string LevelToString(const Level &level) const;

    private:
        Level m_log_level{Level::DEBUG};
        std::mutex m_mutex;
    };
}
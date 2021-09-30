#include "Log.hpp"

#include <cstdarg>

namespace crossmatch 
{
    std::unique_ptr<Log> log = std::make_unique<Log>();
    
    Log::Log()
    {

    }
    
    Log::Log(const Level &level)
        : m_log_level(level)
    {

    }
    
    void Log::SetLevel(const Level &level)
    {
        m_log_level = level;
    }
    
    Level Log::GetLevel() const
    {
        return m_log_level;
    }
    
    void Log::trace(const std::string &msg...)
    {
        if(Level::TRACE >= m_log_level)
        {
            va_list args;
            va_start(args, msg);
            this->LogInternal(Level::TRACE, msg, args);
            va_end(args);
        }
    }
    
    void Log::debug(const std::string &msg...)
    {
        if(Level::DEBUG >= m_log_level)
        {
            va_list args;
            va_start(args, msg);
            this->LogInternal(Level::DEBUG, msg, args);
            va_end(args);
        }
    }
    
    void Log::info(const std::string &msg...)
    {
        if(Level::INFO >= m_log_level)
        {
            va_list args;
            va_start(args, msg);
            this->LogInternal(Level::INFO, msg, args);
            va_end(args);
        }
    }
    
    void Log::warning(const std::string &msg...)
    {
        if(Level::WARNING >= m_log_level)
        {
            va_list args;
            va_start(args, msg);
            this->LogInternal(Level::WARNING, msg, args);
            va_end(args);
        }
    }
    
    void Log::error(const std::string &msg...)
    {
        if(Level::ERROR >= m_log_level)
        {
            va_list args;
            va_start(args, msg);
            this->LogInternal(Level::ERROR, msg, args);
            va_end(args);
        }
    }
    
    void Log::LogInternal(const Level &level, const std::string &msg, va_list args)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::string final_msg = LevelToString(level) + " " + msg + "\n";
        vprintf(final_msg.c_str(), args);
    }
    
    std::string Log::LevelToString(const Level &level) const
    {
        switch(level)
        {
            case Level::TRACE: return "TRACE";
            case Level::DEBUG: return "DEBUG";
            case Level::ERROR: return "ERROR";
            case Level::INFO: return "INFO";
            case Level::WARNING: return "WARNING";
        }

        return "";
    }
}
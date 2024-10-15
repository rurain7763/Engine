#include "pch.h"

#include "Logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace engine {
    std::shared_ptr<spdlog::logger> s_CoreLogger;
    std::shared_ptr<spdlog::logger> s_ClientLogger;

    void Logger::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void Logger::EGTrace(const char* fmt, ...) {
        char buffer[1024];

        va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		s_CoreLogger->trace(buffer);
		va_end(args);
	}

    void Logger::EGInfo(const char* fmt, ...) {
        char buffer[1024];

        va_list args;
		va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        s_CoreLogger->info(buffer);
        va_end(args);
    }

    void Logger::EGWarn(const char* fmt, ...) {
        char buffer[1024];

        va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		s_CoreLogger->warn(buffer);
		va_end(args);
    }

    void Logger::EGError(const char* fmt, ...) {
        char buffer[1024];

        va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		s_CoreLogger->error(buffer);
		va_end(args);
	}

    void Logger::EGFatal(const char* fmt, ...) {
        char buffer[1024];

		va_list args;
        va_start(args, fmt);
		vsprintf(buffer, fmt, args);
        s_CoreLogger->critical(buffer);
		va_end(args);
    }

    void Logger::AppTrace(const char* fmt, ...) {
        char buffer[1024];

        va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		s_ClientLogger->trace(buffer);
		va_end(args);
	}

    void Logger::AppInfo(const char* fmt, ...) {
        char buffer[1024];

		va_list args;
        va_start(args, fmt);
		vsprintf(buffer, fmt, args);
        s_ClientLogger->info(buffer);
		va_end(args);
    }

    void Logger::AppWarn(const char* fmt, ...) {
        char buffer[1024];

	    va_list args;
		va_start(args, fmt);
		vsprintf(buffer, fmt, args);
		s_ClientLogger->warn(buffer);
		va_end(args);
	}

    void Logger::AppError(const char* fmt, ...) {
        char buffer[1024];

	    va_list args;
        va_start(args, fmt);
	    vsprintf(buffer, fmt, args);
        s_ClientLogger->error(buffer);
        va_end(args);
    }

    void Logger::AppFatal(const char* fmt, ...) {
        char buffer[1024];

		va_list args;
		va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        s_ClientLogger->critical(buffer);
        va_end(args);
    }
}
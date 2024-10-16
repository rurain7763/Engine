#ifndef LOGGER_H
#define LOGGER_H

#include "EngineHeader.h"

namespace engine {
    class EG_API Logger {
    public:
        static void Init();

        static void EGTrace(const char* fmt, ...);
        static void EGInfo(const char* fmt, ...);
        static void EGWarn(const char* fmt, ...);
        static void EGError(const char* fmt, ...);
        static void EGFatal(const char* fmt, ...);

        static void AppTrace(const char* fmt, ...);
        static void AppInfo(const char* fmt, ...);
        static void AppWarn(const char* fmt, ...);
        static void AppError(const char* fmt, ...);
        static void AppFatal(const char* fmt, ...);
    };
}

#define EG_LOG_TRACE(fmt, ...) Logger::EGTrace(fmt, ##__VA_ARGS__)
#define EG_LOG_INFO(fmt, ...) Logger::EGInfo(fmt, ##__VA_ARGS__)
#define EG_LOG_WARN(fmt, ...) Logger::EGWarn(fmt, ##__VA_ARGS__)
#define EG_LOG_ERROR(fmt, ...) Logger::EGError(fmt, ##__VA_ARGS__)
#define EG_LOG_FATAL(fmt, ...) Logger::EGFatal(fmt, ##__VA_ARGS__)

#define LOG_TRACE(fmt, ...) Logger::AppTrace(fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) Logger::AppInfo(fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) Logger::AppWarn(fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::AppError(fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) Logger::AppFatal(fmt, ##__VA_ARGS__)

#ifdef PLATFORM_MAC
    #define __debugbreak() __builtin_trap()
#elif PLATFORM_WINDOWS
    #define __debugbreak() __debugbreak()
#endif

#ifdef DEBUG
    #define EG_ASSERT(x, fmt, ...) if(!(x)) { EG_LOG_FATAL("Assertion failure : " fmt, ##__VA_ARGS__); __debugbreak(); }
#elif RELEASE
    #define EG_ASSERT(x, fmt, ...) x
#endif

#endif
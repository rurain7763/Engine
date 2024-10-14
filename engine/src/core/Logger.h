#ifndef LOGGER_H
#define LOGGER_H

#include "EngineHeader.h"
#include "spdlog/spdlog.h"

namespace engine {
    class EG_API Logger {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define LOG_EG_TRACE(...) Logger::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_EG_INFO(...) Logger::getCoreLogger()->info(__VA_ARGS__)
#define LOG_EG_WARN(...) Logger::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_EG_ERROR(...) Logger::getCoreLogger()->error(__VA_ARGS__)
#define LOG_EG_FATAL(...) Logger::getCoreLogger()->critical(__VA_ARGS__)

#define LOG_APP_TRACE(...) Logger::getClientLogger()->trace(__VA_ARGS__)
#define LOG_APP_INFO(...) Logger::getClientLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...) Logger::getClientLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...) Logger::getClientLogger()->error(__VA_ARGS__)
#define LOG_APP_FATAL(...) Logger::getClientLogger()->critical(__VA_ARGS__)

#ifdef PLATFORM_MAC
    #define __debugbreak() __builtin_trap()
#elif PLATFORM_WINDOWS
    #define __debugbreak() __debugbreak()
#endif

#ifdef DEBUG
    #define EG_ASSERT(x, ...) { if(!(x)) { LOG_EG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define EG_ASSERT(x, ...)
#endif

#endif
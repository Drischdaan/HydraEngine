#pragma once

#include <memory>
#include <Engine/Core/CoreDefinitions.h>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

class ENGINE_API FLogManager
{
public:
    static void Initialize();
    static void Shutdown();

    static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
    
private:
    static std::shared_ptr<spdlog::logger> s_EngineLogger;
    static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
    
};

#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

#define APP_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(FLogManager::GetApplicationLogger(), __VA_ARGS__)
#define APP_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(FLogManager::GetApplicationLogger(), __VA_ARGS__)
#define APP_LOG_INFO(...) SPDLOG_LOGGER_INFO(FLogManager::GetApplicationLogger(), __VA_ARGS__)
#define APP_LOG_WARN(...) SPDLOG_LOGGER_WARN(FLogManager::GetApplicationLogger(), __VA_ARGS__)
#define APP_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(FLogManager::GetApplicationLogger(), __VA_ARGS__)
#define APP_LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(FLogManager::GetApplicationLogger(), __VA_ARGS__)
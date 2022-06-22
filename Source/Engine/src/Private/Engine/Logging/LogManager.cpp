#include "pch.h"

#include <Engine/Logging/LogManager.h>

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> FLogManager::s_EngineLogger = nullptr;
std::shared_ptr<spdlog::logger> FLogManager::s_ApplicationLogger = nullptr;

void FLogManager::Initialize()
{
    const std::string pattern = "%^[%D %T] [%=10n] %8l:%$ %v";
    const std::string globalPattern = "%^[%D %T] [%=10n] [%26!s:%-4#] %8l:%$ %v";
    constexpr spdlog::level::level_enum logLevel = spdlog::level::trace;
    constexpr spdlog::level::level_enum flushLevel = spdlog::level::info;
    
    std::vector<spdlog::sink_ptr> engineSinks = {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/Engine/Engine.log", 1048576 * 5, 3, true),
    };

    s_EngineLogger = std::make_shared<spdlog::logger>("Engine", begin(engineSinks), end(engineSinks));
    s_EngineLogger->flush_on(flushLevel);
    s_EngineLogger->set_level(logLevel);
    s_EngineLogger->set_pattern(pattern);
    spdlog::register_logger(s_EngineLogger);

    std::vector<spdlog::sink_ptr> applicationSinks = {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/Application/Application.log", 1048576 * 5, 3, true),
    };

    s_ApplicationLogger = std::make_shared<spdlog::logger>("App", begin(applicationSinks), end(applicationSinks));
    s_ApplicationLogger->flush_on(flushLevel);
    s_ApplicationLogger->set_level(logLevel);
    s_ApplicationLogger->set_pattern(pattern);
    spdlog::register_logger(s_ApplicationLogger);

    spdlog::set_default_logger(s_EngineLogger);
    spdlog::flush_on(flushLevel);
    spdlog::set_level(logLevel);
    spdlog::set_pattern(globalPattern);

    LOG_DEBUG("Logging initialized");
}

void FLogManager::Shutdown()
{
    spdlog::shutdown();
}

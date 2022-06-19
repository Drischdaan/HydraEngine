#pragma once

#include <format>
#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Logging/LogManager.h>

namespace Platform
{
    void ENGINE_API Assert(const std::string& condition, const FStatusCode& code, const char* file, int line, const std::string& message);
}

#define IS_SUCCESS_CODE(code) ((code).Code >= 0)
#define IS_FAILURE_CODE(code) ((code).Code < 0)
#define RETURN_IF_FAILED(code) \
    { \
        ASSERT(!IS_FAILURE_CODE(code), code, "Failed status code") \
        if(IS_FAILURE_CODE(code)) \
            return code; \
    }

#define ASSERTEX(condition, code, ...) \
    if (!(condition)) \
    { \
        LOG_CRITICAL(__VA_ARGS__); \
        Platform::Assert(#condition, code, __FILENAME__, __LINE__, std::format(__VA_ARGS__)); \
        std::exit(code.Code); \
    }

#define ASSERT(condition, code, ...) \
    if (!(condition)) \
    { \
        LOG_CRITICAL(__VA_ARGS__); \
        Platform::Assert(#condition, code, __FILENAME__, __LINE__, std::format(__VA_ARGS__)); \
    }
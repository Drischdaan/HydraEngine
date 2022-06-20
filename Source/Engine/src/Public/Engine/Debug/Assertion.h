#pragma once

#include <format>
#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Logging/LogManager.h>
#include <Engine/Engine.h>

namespace Platform
{
    void ENGINE_API Assert(const std::string& condition, const FStatusCode& code, const char* file, int line, const std::string& message);
}

#define IS_SUCCESS_CODE(code) ((code).Code >= 0)
#define IS_FAILURE_CODE(code) ((code).Code < 0)
#define RETURN_IF_FAILED(code) \
    { \
        const FStatusCode statusCode = code; \
        ASSERT(IS_SUCCESS_CODE(statusCode), statusCode, "Failed status code") \
        if(IS_FAILURE_CODE(statusCode)) \
            return statusCode; \
    }

#define ASSERTEX(condition, code, ...) \
    if (!(condition)) \
    { \
        const FStatusCode statusCode = code; \
        LOG_CRITICAL(__VA_ARGS__); \
        Platform::Assert(#condition, statusCode, __FILENAME__, __LINE__, std::format(__VA_ARGS__)); \
        std::exit(GEngine->Stop(statusCode).Code); \
    }

#define ASSERTRET(condition, code, ...) \
    if (!(condition)) \
    { \
        const FStatusCode statusCode = code; \
        LOG_CRITICAL(__VA_ARGS__); \
        Platform::Assert(#condition, statusCode, __FILENAME__, __LINE__, std::format(__VA_ARGS__)); \
        return statusCode; \
    }

#define ASSERT(condition, code, ...) \
    if (!(condition)) \
    { \
        const FStatusCode statusCode = code; \
        LOG_CRITICAL(__VA_ARGS__); \
        Platform::Assert(#condition, statusCode, __FILENAME__, __LINE__, std::format(__VA_ARGS__)); \
    }
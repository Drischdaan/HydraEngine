#pragma once

#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Core/CoreTypes.h>

#include <string>

struct ENGINE_API FStatusCode
{
    i8 Code;
    std::string Message;

    FStatusCode(char code, std::string message)
        : Code(code), Message(std::move(message))
    {
    }
};

#define DEFINE_STATUS_CODE(name, code, message) \
    static const FStatusCode name = FStatusCode(code, message);

#define IS_SUCCESS_CODE(code) ((code).Code >= 0)
#define IS_FAILURE_CODE(code) ((code).Code < 0)
#define RETURN_IF_FAILED(code) if (IS_FAILURE_CODE(code)) return code;

namespace StatusCode
{
    DEFINE_STATUS_CODE(Ok, 0, "Ok")
    DEFINE_STATUS_CODE(Error, -1, "Error")
    DEFINE_STATUS_CODE(NotImplemented, -2, "Not implemented")
}
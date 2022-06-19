#pragma once

#include <Engine/Core/CoreDefinitions.h>

#include <string>

struct ENGINE_API FStatusCode
{
    int Code;
    std::string Message;

    FStatusCode(int code, std::string message)
        : Code(code), Message(std::move(message))
    {
    }
};

#define DEFINE_STATUS_CODE(name, code, message) \
    static const FStatusCode name = FStatusCode(code, message);

namespace StatusCode
{
    DEFINE_STATUS_CODE(Ok, 0, "Ok")
    DEFINE_STATUS_CODE(Error, -1, "Error")
    DEFINE_STATUS_CODE(NotImplemented, -2, "Not implemented")
}
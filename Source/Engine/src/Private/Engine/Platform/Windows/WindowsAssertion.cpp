#include "pch.h"

#include <Engine/Debug/Assertion.h>

#ifdef _PLATFORM_WINDOWS
#include <Windows.h>

void Platform::Assert(const std::string& condition, const FStatusCode& code, const char* file, int line, const std::string& message)
{
    const std::string formattedMessage = std::format("Condition: {}\nFile: {}\nLine: {}\nCode: {} ({})\n\n\nMessage: {}", condition, file, line, code.Code, code.Message, message);
    MessageBoxA(nullptr, formattedMessage.c_str(), "Assertion failed", MB_OK | MB_ICONERROR);
}
#endif
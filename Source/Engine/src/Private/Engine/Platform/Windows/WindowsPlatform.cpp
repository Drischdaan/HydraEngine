#include "pch.h"

#include <Engine/Platform/Platform.h>

#ifdef _PLATFORM_WINDOWS

FStatusCode Platform::Initialize()
{
    return StatusCode::Ok;
}

void Platform::Shutdown()
{
    
}

#endif
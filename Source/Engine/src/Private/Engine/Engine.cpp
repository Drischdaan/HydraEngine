#include "pch.h"

#include <Engine/Engine.h>

void FEngine::Start(FEngineSpecification specification)
{
    m_EngineSpecification = specification;
    Initialize();
    Run();
    Shutdown();
}

void FEngine::Initialize()
{
}

void FEngine::Run()
{
}

void FEngine::Shutdown()
{
}
#include "pch.h"

#include <Engine/Engine.h>

#include <utility>

FStatusCode FEngine::Start(FEngineSpecification specification, std::shared_ptr<FApplication> application)
{
    m_EngineSpecification = specification;
    m_Application = std::move(application);
    if(IS_FAILURE_CODE(Initialize()))
        return Shutdown();
    Run();
    return Shutdown();
}

FStatusCode FEngine::Initialize() const
{
    FStatusCode applicationStatus = m_Application->Initialize();
    RETURN_IF_FAILED(applicationStatus)
    return StatusCode::Ok;
}

void FEngine::Run()
{
}

FStatusCode FEngine::Shutdown() const
{
    if(m_Application != nullptr)
    {
        FStatusCode applicationStatus = m_Application->Shutdown();
        RETURN_IF_FAILED(applicationStatus)
    }
    return StatusCode::Ok;
}
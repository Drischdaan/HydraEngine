#include "pch.h"

#include <Engine/Engine.h>

#include <utility>

FStatusCode FEngine::Start(FEngineSpecification specification, std::shared_ptr<FApplication> application)
{
    m_EngineSpecification = specification;
    m_Application = std::move(application);
    const FStatusCode initializationCode = Initialize();
    if(IS_FAILURE_CODE(initializationCode))
        return Shutdown(initializationCode);
    Run();
    return Shutdown(initializationCode);
}

FStatusCode FEngine::Initialize() const
{
    FStatusCode applicationStatus = m_Application->Initialize();
    RETURN_IF_FAILED(applicationStatus)
    return StatusCode::Ok;
}

void FEngine::Run() const
{
}

FStatusCode FEngine::Shutdown(FStatusCode code) const
{
    if(m_Application != nullptr)
    {
        FStatusCode applicationStatus = m_Application->Shutdown();
        RETURN_IF_FAILED(applicationStatus)
    }
    return code;
}
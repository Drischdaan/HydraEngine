#include "pch.h"

#include <iostream>
#include <Engine/Engine.h>

#include <utility>

#include "Engine/Debug/Assertion.h"
#include "Engine/Logging/LogManager.h"
#include "Engine/Platform/Platform.h"

FStatusCode FEngine::Start(FEngineSpecification specification, std::shared_ptr<FApplication> application)
{
    m_EngineSpecification = specification;
    m_Application = std::move(application);
    FStatusCode initializationCode = Initialize();
    if(IS_FAILURE_CODE(initializationCode))
        return initializationCode;
    Run();
    return StatusCode::Ok;
}

FStatusCode FEngine::Stop(FStatusCode code) const
{
    return Shutdown(std::move(code));
}

FStatusCode FEngine::Initialize()
{
    FLogManager::Initialize();
    RETURN_IF_FAILED(Platform::Initialize())
    
    LOG_INFO("Hydra Engine {}", VERSION_STRING(ENGINE_VERSION, std::string(ENGINE_VERSION_SUFFIX)));
    LOG_DEBUG("Loading application...");
    RETURN_IF_FAILED(m_Application->Initialize())
    
    const FApplicationSpecification applicationSpecification = m_Application->GetApplicationSpecification();
    LOG_INFO("Application initialized:");
    LOG_INFO("\tName: " + applicationSpecification.Name);
    LOG_INFO("\tAuthor: " + applicationSpecification.Author);
    LOG_INFO("\tVersion: " + VERSION_STRING(applicationSpecification.Version, applicationSpecification.VersionSuffix));

    FRendererSpecification rendererSpecification;
    m_Renderer = std::make_shared<FRenderer>(rendererSpecification);
    ASSERT(m_Renderer != nullptr, StatusCode::InvalidRenderer, "Failed to create renderer")
    RETURN_IF_FAILED(m_Renderer->Initialize())
    return StatusCode::Ok;
}

void FEngine::Run() const
{
}

FStatusCode FEngine::Shutdown(FStatusCode code) const
{
    m_Renderer->Shutdown();
    if(m_Application != nullptr)
    {
        const FStatusCode applicationStatus = m_Application->Shutdown();
        ASSERT(!IS_FAILURE_CODE(applicationStatus), applicationStatus, "Failed status code")
    }
    Platform::Shutdown();
    FLogManager::Shutdown();
#ifdef _DEBUG
    printf("Press [ENTER] to exit...");
    std::cin.get();
#endif
    return code;
}
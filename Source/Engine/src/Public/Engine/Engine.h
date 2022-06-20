#pragma once

#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Core/StatusCodes.h>

#include <memory>

#include "Application/Application.h"
#include "Renderer/Renderer.h"

struct ENGINE_API FEngineSpecification
{
    
};

class ENGINE_API FEngine
{
public:
    FEngine() = default;
    ~FEngine() = default;

    FStatusCode Start(FEngineSpecification specification, std::shared_ptr<FApplication> application);
    [[nodiscard]] FStatusCode Stop(FStatusCode code) const;

    [[nodiscard]] FEngineSpecification GetEngineSpecification() const { return m_EngineSpecification; }

private:
    [[nodiscard]] FStatusCode Initialize();
    void Run() const;
    [[nodiscard]] FStatusCode Shutdown(FStatusCode code) const;
    
private:
    FEngineSpecification m_EngineSpecification{};
    std::shared_ptr<FApplication> m_Application = nullptr;
    std::shared_ptr<FRenderer> m_Renderer = nullptr;
    
};

#define ENGINE_VERSION VERSION(0, 1, 0)
#define ENGINE_VERSION_SUFFIX "alpha"

static FEngine* GEngine = new FEngine();
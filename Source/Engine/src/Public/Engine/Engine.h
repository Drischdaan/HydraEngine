#pragma once

#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Core/StatusCodes.h>

#include <memory>

#include "Application/Application.h"

struct ENGINE_API FEngineSpecification
{
    
};

class ENGINE_API FEngine
{
public:
    FEngine() = default;
    ~FEngine() = default;

    FStatusCode Start(FEngineSpecification specification, std::shared_ptr<FApplication> application);

    [[nodiscard]] FEngineSpecification GetEngineSpecification() const { return m_EngineSpecification; }

private:
    [[nodiscard]] FStatusCode Initialize() const;
    void Run() const;
    [[nodiscard]] FStatusCode Shutdown(FStatusCode code) const;
    
private:
    FEngineSpecification m_EngineSpecification{};
    std::shared_ptr<FApplication> m_Application = nullptr;
    
};

static std::shared_ptr<FEngine> GEngine = std::make_shared<FEngine>();
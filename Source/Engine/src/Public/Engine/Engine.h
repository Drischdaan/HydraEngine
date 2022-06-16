#pragma once

#include <memory>
#include <Engine/Core/CoreDefinitions.h>

struct ENGINE_API FEngineSpecification
{
    
};

class ENGINE_API FEngine
{
public:
    FEngine() = default;
    ~FEngine() = default;

    void Start(FEngineSpecification specification);

    [[nodiscard]] FEngineSpecification GetEngineSpecification() const { return m_EngineSpecification; }

private:
    void Initialize();
    void Run();
    void Shutdown();
    
private:
    FEngineSpecification m_EngineSpecification{};
    
};

static std::shared_ptr<FEngine> GEngine = std::make_shared<FEngine>();
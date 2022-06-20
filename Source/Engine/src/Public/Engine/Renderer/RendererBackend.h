#pragma once

#include <memory>
#include <Engine/Core/CoreDefinitions.h>

enum class ENGINE_API ERendererBackend
{
    OpenGL,
    DirectX11,
    DirectX12,
    Vulkan,
};

struct ENGINE_API FRendererBackendSpecification
{
    ERendererBackend BackendType = ERendererBackend::Vulkan;
};

class ENGINE_API FRendererBackend
{
public:
    FRendererBackend(FRendererBackendSpecification specification)
        : m_Specification(specification) {}
    virtual ~FRendererBackend() = default;

    virtual FStatusCode Initialize() = 0;
    virtual void Shutdown() = 0;

    [[nodiscard]] FRendererBackendSpecification GetSpecification() const { return m_Specification; }

public:
    static std::shared_ptr<FRendererBackend> Create(FRendererBackendSpecification specification);
    
private:
    FRendererBackendSpecification m_Specification;
    
};
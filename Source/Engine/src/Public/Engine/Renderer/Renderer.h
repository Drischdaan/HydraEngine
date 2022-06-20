#pragma once

#include <memory>
#include <Engine/Core/CoreDefinitions.h>

#include "RendererBackend.h"

struct ENGINE_API FRendererSpecification
{
    ERendererBackend BackendType = ERendererBackend::Vulkan;
};

class ENGINE_API FRenderer
{
public:
    FRenderer(FRendererSpecification specification);
    ~FRenderer() = default;

    FStatusCode Initialize();
    void Update() const;
    void Shutdown() const;

    [[nodiscard]] FRendererSpecification GetSpecification() const { return m_Specification; }

private:
    FRendererSpecification m_Specification;
    std::shared_ptr<FRendererBackend> m_RendererBackend;
    
};
#include "pch.h"

#include <Engine/Renderer/RendererBackend.h>

#include "Engine/Debug/Assertion.h"
#include "Engine/Renderer/Backends/Vulkan/VulkanRendererBackend.h"

std::shared_ptr<FRendererBackend> FRendererBackend::Create(FRendererBackendSpecification specification)
{
    switch (specification.BackendType)
    {
    case ERendererBackend::Vulkan:
        return std::make_shared<FVulkanRendererBackend>(specification);
    case ERendererBackend::OpenGL:
    case ERendererBackend::DirectX11:
    case ERendererBackend::DirectX12:
        ASSERT(false, StatusCode::NotImplemented, "Renderer backend not implemented")
        break;
    default:
        ASSERTEX(false, StatusCode::InvalidRendererBackend, "Unknown backend type")
        break;
    }
    return nullptr;
}

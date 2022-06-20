#include "pch.h"

#include <Engine/Renderer/Renderer.h>

#include "Engine/Debug/Assertion.h"

FRenderer::FRenderer(FRendererSpecification specification)
    : m_Specification(specification)
{
}

FStatusCode FRenderer::Initialize()
{
    FRendererBackendSpecification backendSpecification;
    backendSpecification.BackendType = m_Specification.BackendType;
    m_RendererBackend = FRendererBackend::Create(backendSpecification);
    ASSERT(m_RendererBackend != nullptr, StatusCode::InvalidRendererBackend, "Failed to create renderer backend")
    RETURN_IF_FAILED(m_RendererBackend->Initialize())
    return StatusCode::Ok;
}

void FRenderer::Update() const
{
}

void FRenderer::Shutdown() const
{
    m_RendererBackend->Shutdown();
}

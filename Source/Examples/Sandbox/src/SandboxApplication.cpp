#include <SandboxApplication.h>

SandboxApplication::SandboxApplication(const FApplicationSpecification& specification)
    : FApplication(specification)
{
}

FStatusCode SandboxApplication::Initialize()
{
    return StatusCode::Ok;
}

FStatusCode SandboxApplication::Shutdown()
{
    return StatusCode::Ok;
}

#pragma once

#include <Engine/Application/Application.h>

class SandboxApplication : public FApplication
{
public:
    explicit SandboxApplication(const FApplicationSpecification& specification);

    FStatusCode Initialize() override;
    FStatusCode Shutdown() override;

private:
    
};
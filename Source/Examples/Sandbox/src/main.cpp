﻿#include <Engine/Engine.h>

#include "SandboxApplication.h"

int main()
{
    FApplicationSpecification appSpecification;
    appSpecification.Name = "Sandbox";
    appSpecification.Author = "HydraStudio";
    appSpecification.Version = VERSION(1, 0, 0);
    appSpecification.VersionSuffix = "alpha";
    constexpr FEngineSpecification specification;
    const FStatusCode startCode = GEngine->Start(specification, std::make_shared<SandboxApplication>(appSpecification));
    const FStatusCode stopCode = GEngine->Stop(startCode);
    delete GEngine;
    return stopCode.Code;
}

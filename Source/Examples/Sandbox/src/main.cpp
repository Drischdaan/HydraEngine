#include <Engine/Engine.h>

#include "SandboxApplication.h"

int main()
{
    FApplicationSpecification appSpecification;
    appSpecification.Name = "Sandbox";
    appSpecification.Author = "HydraStudio";
    appSpecification.MajorVersion = 1;
    appSpecification.MinorVersion = 0;
    appSpecification.PatchVersion = 0;
    appSpecification.VersionSuffix = "build";
    constexpr FEngineSpecification specification;
    return GEngine->Start(specification, std::make_shared<SandboxApplication>(appSpecification)).Code;
}
#include <Engine/Engine.h>

#include "SandboxApplication.h"

int main()
{
    FApplicationSpecification appSpecification;
    appSpecification.Name = "Sandbox";
    appSpecification.Author = "HydraStudio";
    appSpecification.Version = VERSION(1, 0, 0);
    appSpecification.VersionSuffix = "build";
    constexpr FEngineSpecification specification;
    return GEngine->Start(specification, std::make_shared<SandboxApplication>(appSpecification)).Code;
}
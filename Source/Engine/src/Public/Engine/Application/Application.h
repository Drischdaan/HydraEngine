#pragma once

#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Core/StatusCodes.h>

struct ENGINE_API FApplicationSpecification
{
    std::string Name = "Unnamed";
    std::string Author = "Unnamed";
    i8 MajorVersion = 0;
    i8 MinorVersion = 0;
    i8 PatchVersion = 0;
    std::string VersionSuffix = "dev";
};

class ENGINE_API FApplication
{
public:
    FApplication(FApplicationSpecification specification)
        : m_ApplicationSpecification(std::move(specification)) {}
    virtual ~FApplication() = default;

    virtual FStatusCode Initialize() = 0;
    virtual FStatusCode Shutdown() = 0;

    [[nodiscard]] FApplicationSpecification GetApplicationSpecification() const { return m_ApplicationSpecification; }

private:
    FApplicationSpecification m_ApplicationSpecification;
    
};
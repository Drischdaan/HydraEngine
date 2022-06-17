#pragma once

#include <Engine/Core/CoreDefinitions.h>
#include <Engine/Core/StatusCodes.h>

struct ENGINE_API FApplicationSpecification
{
    std::string Name = "Unnamed";
    std::string Author = "Unnamed";
    u32 Version = VERSION(0, 0, 0);
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

protected:
    FApplicationSpecification m_ApplicationSpecification;
    
};
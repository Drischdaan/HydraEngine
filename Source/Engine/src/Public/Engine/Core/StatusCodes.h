#pragma once

#include <Engine/Core/CoreDefinitions.h>

#include <string>

struct ENGINE_API FStatusCode
{
    int Code;
    std::string Message;

    FStatusCode(int code, std::string message)
        : Code(code), Message(std::move(message))
    {
    }
};

#define DEFINE_STATUS_CODE(name, code, message) \
    static const FStatusCode name = FStatusCode(code, message);

namespace StatusCode
{
    DEFINE_STATUS_CODE(Ok, 0, "Ok")
    DEFINE_STATUS_CODE(Error, -1, "Error")
    DEFINE_STATUS_CODE(NotImplemented, -2, "Not implemented")
    DEFINE_STATUS_CODE(InvalidRenderer, -3, "Invalid renderer")
    DEFINE_STATUS_CODE(InvalidRendererBackend, -4, "Invalid renderer backend")
    DEFINE_STATUS_CODE(InvalidVulkanInstance, -100, "Invalid Vulkan instance")
    DEFINE_STATUS_CODE(InvalidVulkanPhysicalDevice, -101, "Invalid Vulkan physical device")
    DEFINE_STATUS_CODE(InvalidVulkanDevice, -102, "Invalid Vulkan device")
    DEFINE_STATUS_CODE(RequiredExtensionNotSupported, -103, "Required Vulkan extension not supported")
    DEFINE_STATUS_CODE(RequiredLayerNotSupported, -104, "Required Vulkan layer not supported")
    DEFINE_STATUS_CODE(InvalidQueueName, -105, "Invalid queue name")
}
#pragma once

#include <Engine/Renderer/RendererBackend.h>

#include <vulkan/vulkan.h>

class ENGINE_API FVulkanRendererBackend : public FRendererBackend
{
public:
    explicit FVulkanRendererBackend(const FRendererBackendSpecification& specification);

    FStatusCode Initialize() override;
    void Shutdown() override;

private:
    FStatusCode CreateInstance();
    FStatusCode AcquirePhysicalDevice();
    FStatusCode CreateDevice();

    [[nodiscard]] const char* GetVendorName(uint32_t vendorId) const;
    
private:
    VkInstance m_VulkanInstance = VK_NULL_HANDLE;
    
    VkPhysicalDevice m_VulkanPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties m_VulkanPhysicalDeviceProperties = {};
    VkPhysicalDeviceFeatures m_VulkanPhysicalDeviceFeatures = {};
    VkPhysicalDeviceMemoryProperties m_VulkanPhysicalDeviceMemoryProperties = {};

    VkDevice m_VulkanDevice = VK_NULL_HANDLE;
    
};
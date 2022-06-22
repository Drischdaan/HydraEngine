#pragma once

#include <Engine/Renderer/RendererBackend.h>

#include <vulkan/vulkan.h>

struct ENGINE_API FQueueFamilyIndices
{
    uint32_t GraphicsFamily = UINT32_MAX;
    uint32_t ComputeFamily = UINT32_MAX;
    uint32_t PresentFamily = UINT32_MAX;
    uint32_t TransferFamily = UINT32_MAX;
};

struct ENGINE_API FQueueListEntry
{
    const char* Name;
    uint32_t QueueFamilyIndex;
    uint32_t QueueIndex;
    bool WasCreated;
};

class ENGINE_API FVulkanRendererBackend : public FRendererBackend
{
public:
    explicit FVulkanRendererBackend(const FRendererBackendSpecification& specification);

    FStatusCode Initialize() override;
    void Shutdown() override;

private:
    FStatusCode CreateInstance();
    FStatusCode AcquirePhysicalDevice();
    FStatusCode CreateDevice(VkPhysicalDeviceFeatures physicalDeviceFeatures);

    [[nodiscard]] const char* GetVendorName(uint32_t vendorId) const;
    
private:
    VkInstance m_VulkanInstance = VK_NULL_HANDLE;
    
    VkPhysicalDevice m_VulkanPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties m_VulkanPhysicalDeviceProperties = {};
    VkPhysicalDeviceFeatures m_VulkanPhysicalDeviceFeatures = {};
    VkPhysicalDeviceMemoryProperties m_VulkanPhysicalDeviceMemoryProperties = {};
    FQueueFamilyIndices m_QueueFamilyIndices = {};

    VkDevice m_VulkanDevice = VK_NULL_HANDLE;
    VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
    VkQueue m_ComputeQueue = VK_NULL_HANDLE;
    VkQueue m_PresentQueue = VK_NULL_HANDLE;
    VkQueue m_TransferQueue = VK_NULL_HANDLE;
    
};
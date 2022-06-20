#include "pch.h"

#include <Engine/Renderer/Backends/Vulkan/VulkanRendererBackend.h>

#include "Engine/Debug/Assertion.h"

FVulkanRendererBackend::FVulkanRendererBackend(const FRendererBackendSpecification& specification)
    : FRendererBackend(specification)
{
}

FStatusCode FVulkanRendererBackend::Initialize()
{
    RETURN_IF_FAILED(CreateInstance())
    RETURN_IF_FAILED(AcquirePhysicalDevice())
    RETURN_IF_FAILED(CreateDevice())
    return StatusCode::Ok;
}

void FVulkanRendererBackend::Shutdown()
{
    vkDestroyDevice(m_VulkanDevice, nullptr);
    vkDestroyInstance(m_VulkanInstance, nullptr);
}

FStatusCode FVulkanRendererBackend::CreateInstance()
{
    VkApplicationInfo applicationInfo;
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext = nullptr;
    applicationInfo.pApplicationName = "Hydra";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "Hydra";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledLayerNames = nullptr;
    instanceCreateInfo.enabledExtensionCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = nullptr;

    const VkResult instanceCreateResult = vkCreateInstance(&instanceCreateInfo, nullptr, &m_VulkanInstance);
    ASSERTRET(instanceCreateResult == VK_SUCCESS, StatusCode::InvalidVulkanInstance, "Failed to create Vulkan instance")
    LOG_DEBUG("Created Vulkan instance");
    return StatusCode::Ok;
}

FStatusCode FVulkanRendererBackend::AcquirePhysicalDevice()
{
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(m_VulkanInstance, &physicalDeviceCount, nullptr);
    ASSERTRET(physicalDeviceCount > 0, StatusCode::InvalidVulkanPhysicalDevice, "Failed to find Vulkan physical device")
    LOG_DEBUG("Found {} Vulkan physical device{}", physicalDeviceCount, physicalDeviceCount > 1 ? "s" : "");
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(m_VulkanInstance, &physicalDeviceCount, physicalDevices.data());

    for (const VkPhysicalDevice physicalDevice : physicalDevices)
    {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
        LOG_DEBUG("\t- {}", physicalDeviceProperties.deviceName);
        if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            m_VulkanPhysicalDevice = physicalDevice;
            m_VulkanPhysicalDeviceProperties = physicalDeviceProperties;
            break;
        }
    }

    LOG_DEBUG("Selected physical device: {} ({})", m_VulkanPhysicalDeviceProperties.deviceName, GetVendorName(m_VulkanPhysicalDeviceProperties.vendorID));
    vkGetPhysicalDeviceFeatures(m_VulkanPhysicalDevice, &m_VulkanPhysicalDeviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(m_VulkanPhysicalDevice, &m_VulkanPhysicalDeviceMemoryProperties);
    
    ASSERTRET(m_VulkanPhysicalDevice != VK_NULL_HANDLE, StatusCode::InvalidVulkanPhysicalDevice, "Failed to find Vulkan physical device") 
    return StatusCode::Ok;
}

FStatusCode FVulkanRendererBackend::CreateDevice()
{
    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.queueCreateInfoCount = 0;
    deviceCreateInfo.pQueueCreateInfos = nullptr;
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = 0;
    deviceCreateInfo.ppEnabledExtensionNames = nullptr;
    deviceCreateInfo.pEnabledFeatures = nullptr;

    const VkResult deviceCreateResult = vkCreateDevice(m_VulkanPhysicalDevice, &deviceCreateInfo, nullptr, &m_VulkanDevice);
    ASSERTRET(deviceCreateResult == VK_SUCCESS, StatusCode::InvalidVulkanDevice, "Failed to create Vulkan device")
    LOG_DEBUG("Created Vulkan device");
    return StatusCode::Ok;
}

const char* FVulkanRendererBackend::GetVendorName(uint32_t vendorId) const
{
    switch (vendorId)
    {
        case 0x1002: return "AMD";
        case 0x1010: return "ImgTec";
        case 0x10DE: return "NVIDIA";
        case 0x13B5: return "ARM";
        case 0x5143: return "Qualcomm";
        case 0x8086: return "INTEL";
        default: return "UNKNOWN";
    }
}
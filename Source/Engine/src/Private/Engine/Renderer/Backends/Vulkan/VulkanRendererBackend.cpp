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

    constexpr VkPhysicalDeviceFeatures enabledFeatures = {};
    RETURN_IF_FAILED(CreateDevice(enabledFeatures))

    LOG_INFO("Vulkan renderer backend initialized");
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

    const std::vector<const char*> requiredExtensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef _PLATFORM_WINDOWS
        "VK_KHR_win32_surface",
#endif
    };

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

    LOG_TRACE("Available Vulkan extensions:");
    for (const auto& extension : extensionProperties)
        LOG_TRACE("\t{}", extension.extensionName);

    LOG_DEBUG("Active Vulkan extensions:");
    for (const char* requiredExtension : requiredExtensions)
    {
        bool found = false;
        for (const VkExtensionProperties& extensionProperty : extensionProperties)
        {
            if (strcmp(extensionProperty.extensionName, requiredExtension) == 0)
            {
                found = true;
                break;
            }
        }
        ASSERTRET(found, StatusCode::RequiredExtensionNotSupported, "Required extension not supported: %s", requiredExtension)
        LOG_DEBUG("\t{}", requiredExtension);
    }

    const std::vector<const char*> requiredLayers = {
#ifdef _DEBUG
        "VK_LAYER_KHRONOS_validation",
#endif
    };

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layerProperties(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

    LOG_TRACE("Found {} Vulkan layer{}:", layerCount, layerCount == 1 ? "" : "s");
    for (const auto& layer : layerProperties)
        LOG_TRACE("\t{}", layer.layerName);

    LOG_DEBUG("Active Vulkan layers:");
    for (const char* requiredLayer : requiredLayers)
    {
        bool found = false;
        for (const VkLayerProperties& layerProperty : layerProperties)
        {
            if (strcmp(layerProperty.layerName, requiredLayer) == 0)
            {
                found = true;
                break;
            }
        }
        ASSERTRET(found, StatusCode::RequiredLayerNotSupported, "Required layer not supported: %s", requiredLayer)
        LOG_DEBUG("\t{}", requiredLayer);
    }
        
    VkInstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
    instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

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
    LOG_DEBUG("Found {} Vulkan physical device{}:", physicalDeviceCount, physicalDeviceCount > 1 ? "s" : "");
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

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_VulkanPhysicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_VulkanPhysicalDevice, &queueFamilyCount, queueFamilyProperties.data());

    uint32_t queueFamilyIndex = 0;
    for (const VkQueueFamilyProperties queueFamilyProperty : queueFamilyProperties)
    {
        if (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            m_QueueFamilyIndices.GraphicsFamily = queueFamilyIndex;
        else if (queueFamilyProperty.queueFlags & VK_QUEUE_COMPUTE_BIT)
            m_QueueFamilyIndices.ComputeFamily = queueFamilyIndex;
        else if (queueFamilyProperty.queueFlags & VK_QUEUE_TRANSFER_BIT)
            m_QueueFamilyIndices.TransferFamily = queueFamilyIndex;

        // TODO: Integrate glfw to provide a window handle to the function
        // VkBool32 presentSupport = false;
        // vkGetPhysicalDeviceSurfaceSupportKHR(m_VulkanPhysicalDevice, queueFamilyIndex, nullptr, &presentSupport);
        // if(presentSupport)
        //     m_QueueFamilyIndices.PresentFamily = queueFamilyIndex;
        queueFamilyIndex++;
    }
    
    ASSERTRET(m_VulkanPhysicalDevice != VK_NULL_HANDLE, StatusCode::InvalidVulkanPhysicalDevice, "Failed to find Vulkan physical device") 
    return StatusCode::Ok;
}

FStatusCode FVulkanRendererBackend::CreateDevice(VkPhysicalDeviceFeatures physicalDeviceFeatures)
{
    const std::vector<FQueueListEntry> queueListEntries = {
        FQueueListEntry{ "GraphicsQueue", m_QueueFamilyIndices.GraphicsFamily, 0, false },
        FQueueListEntry{ "ComputeQueue", m_QueueFamilyIndices.ComputeFamily, 0, false },
        FQueueListEntry{ "TransferQueue", m_QueueFamilyIndices.TransferFamily, 0, false },
        FQueueListEntry{ "PresentQueue", m_QueueFamilyIndices.PresentFamily, 0, false },
    };
    
    constexpr float queuePriority = 1.0f;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (const FQueueListEntry queueListEntry : queueListEntries)
    {
        if(queueListEntry.WasCreated || queueListEntry.QueueFamilyIndex == UINT32_MAX)
            continue;
        std::vector<FQueueListEntry> queueList;
        uint32_t index = 0;
        for (FQueueListEntry listEntry : queueListEntries)
        {
            if(listEntry.QueueFamilyIndex == queueListEntry.QueueFamilyIndex)
            {
                listEntry.QueueIndex = index;
                listEntry.WasCreated = true;
                queueList.push_back(listEntry);
                index++;
            }
        }
        VkDeviceQueueCreateInfo queueCreateInfo;
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.pNext = nullptr;
        queueCreateInfo.flags = 0;
        queueCreateInfo.queueFamilyIndex = queueListEntry.QueueFamilyIndex;
        queueCreateInfo.queueCount = static_cast<uint32_t>(queueList.size());
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    const std::vector<const char*> requiredExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(m_VulkanPhysicalDevice, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    vkEnumerateDeviceExtensionProperties(m_VulkanPhysicalDevice, nullptr, &extensionCount, extensionProperties.data());

    LOG_TRACE("Found {} Vulkan device extension{}:", extensionCount, extensionCount > 1 ? "s" : "");
    for (const VkExtensionProperties extensionProperty : extensionProperties)
        LOG_TRACE("\t- {}", extensionProperty.extensionName);

    LOG_DEBUG("Active device extensions:");
    for (const char* requiredExtension : requiredExtensions)
    {
        bool found = false;
        for (const VkExtensionProperties extensionProperty : extensionProperties)
        {
            if (strcmp(requiredExtension, extensionProperty.extensionName) == 0)
            {
                found = true;
                break;
            }
        }
        ASSERTRET(found, StatusCode::InvalidVulkanDevice, "Failed to find required Vulkan device extension")
        LOG_DEBUG("\t- {}", requiredExtension);
    }
    
    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

    const VkResult deviceCreateResult = vkCreateDevice(m_VulkanPhysicalDevice, &deviceCreateInfo, nullptr, &m_VulkanDevice);
    ASSERTRET(deviceCreateResult == VK_SUCCESS, StatusCode::InvalidVulkanDevice, "Failed to create Vulkan device")
    LOG_DEBUG("Created Vulkan device");

    LOG_DEBUG("Device queues:");
    for (FQueueListEntry entry : queueListEntries)
    {
        if(entry.QueueFamilyIndex != UINT32_MAX)
        {
            if(strcmp(entry.Name, "GraphicsQueue") == 0)
                vkGetDeviceQueue(m_VulkanDevice, entry.QueueFamilyIndex, entry.QueueIndex, &m_GraphicsQueue);
            else if (strcmp(entry.Name, "ComputeQueue") == 0)
                vkGetDeviceQueue(m_VulkanDevice, entry.QueueFamilyIndex, entry.QueueIndex, &m_ComputeQueue);
            else if (strcmp(entry.Name, "TransferQueue") == 0)
                vkGetDeviceQueue(m_VulkanDevice, entry.QueueFamilyIndex, entry.QueueIndex, &m_TransferQueue);
            else if(strcmp(entry.Name, "PresentQueue") == 0)
                vkGetDeviceQueue(m_VulkanDevice, entry.QueueFamilyIndex, entry.QueueIndex, &m_PresentQueue);
        }
    }
    
    LOG_DEBUG("\t- Graphics({}) -> {}", m_QueueFamilyIndices.GraphicsFamily, m_GraphicsQueue != VK_NULL_HANDLE ? "Created" : "Not created");
    LOG_DEBUG("\t- Compute({}) -> {}", m_QueueFamilyIndices.ComputeFamily, m_ComputeQueue != VK_NULL_HANDLE ? "Created" : "Not created");
    LOG_DEBUG("\t- Transfer({}) -> {}", m_QueueFamilyIndices.TransferFamily, m_TransferQueue != VK_NULL_HANDLE ? "Created" : "Not created");
    LOG_DEBUG("\t- Present({}) -> {}", m_QueueFamilyIndices.PresentFamily, m_PresentQueue != VK_NULL_HANDLE ? "Created" : "Not created");
    
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
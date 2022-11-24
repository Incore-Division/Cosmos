#include "VKDevice.h"

namespace Cosmos
{
	VKDevice::VKDevice(SharedRef<Window>& window, SharedRef<VKInstance>& instance)
		: m_Window(window), m_Instance(instance)
	{
		COSMOS_TRACE("Creating Vulkan Device");

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance->GetNativeInstance(), &deviceCount, nullptr);

		COSMOS_ASSERT(deviceCount != 0, "Failed to gpu with vulkan support");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance->GetNativeInstance(), &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (IsDeviceSuitable(device))
			{
				m_PhysicalDevice = device;
				break;
			}
		}

		COSMOS_ASSERT(m_PhysicalDevice != nullptr, "Failed to find a suitable gpu");
	}

	VKDevice::~VKDevice()
	{

	}

	bool VKDevice::IsDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = FindQueueFamilies(device);

		return indices.IsComplete();
	}

	QueueFamilyIndices VKDevice::FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) indices.graphics = i;
			if (indices.IsComplete()) break;
			i++;
		}

		return indices;
	}
}
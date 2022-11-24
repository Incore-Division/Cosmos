#pragma once

#include <optional>

#include "Core/Window.h"
#include "VKInstance.h"

namespace Cosmos
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphics;

		// verify if all queues have values
		bool IsComplete() { return graphics.has_value(); }
	};

	class VKDevice
	{
	public:

		// constructor
		VKDevice(SharedRef<Window>& window, SharedRef<VKInstance>& instance);

		// destructor
		~VKDevice();

	public:

		// veryifies if choosen physical device is appropriated given needed specifications
		bool IsDeviceSuitable(VkPhysicalDevice device);

		// finds and return neccessary family queues 
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	private:

		SharedRef<Window>& m_Window;
		SharedRef<VKInstance>& m_Instance;
		VkPhysicalDevice m_PhysicalDevice{ VK_NULL_HANDLE };

	};
}
#pragma once

#include <vector>

#include "Core/Window.h"

namespace Cosmos
{
	class VKInstance
	{
	public:

		// constructor
		VKInstance(SharedRef<Window>& window, bool validations);

		// destructor
		~VKInstance();

		// returns the native vulkan instance
		inline VkInstance& GetNativeInstance() { return m_Instance; }

	public:

		// returns a list of required extensions for instance's creation
		std::vector<const char*> GetRequiredExtensions();

		// checks if validation layers is supported
		bool CheckValidationLayersSupport();

		// fills debugmessenger create info struct accordingly
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& ci);

	private:

		SharedRef<Window>& m_Window;
		bool m_Validations;
		VkInstance m_Instance{ VK_NULL_HANDLE };
		VkDebugUtilsMessengerEXT m_DebugMessenger{ VK_NULL_HANDLE };
		const std::vector<const char*> m_ValidationsLayers = { "VK_LAYER_KHRONOS_validation" };
	};
}

namespace Cosmos
{
	// creates a debugutilsmessenger
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	// destroys a debugutilsmessenger object previously created
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	// function that any vulkan error reports to
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
}

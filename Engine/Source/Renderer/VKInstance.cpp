#include "VKInstance.h"

namespace Cosmos
{
	VKInstance::VKInstance(SharedRef<Window>& window, bool validations)
		: m_Window(window), m_Validations(validations)
	{
		COSMOS_TRACE("Creating Renderer Instance");

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = m_Window->GetTitle();
		appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
		appInfo.pEngineName = "Cosmos";
		appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
		appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);

		VkDebugUtilsMessengerCreateInfoEXT dci{};
		auto extensions = GetRequiredExtensions();

		VkInstanceCreateInfo ici{};
		ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ici.flags = 0;
		ici.pApplicationInfo = &appInfo;
		ici.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		ici.ppEnabledExtensionNames = extensions.data();

		if (m_Validations)
		{
			ici.enabledLayerCount = static_cast<uint32_t>(m_ValidationsLayers.size());
			ici.ppEnabledLayerNames = m_ValidationsLayers.data();

			PopulateDebugMessengerCreateInfo(dci);
			ici.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&dci;
		}

		else
		{
			ici.enabledLayerCount = 0;
			ici.pNext = nullptr;
		}

		COSMOS_ASSERT(vkCreateInstance(&ici, nullptr, &m_Instance) == VK_SUCCESS, "Failed to create Vulkan Instance");

		if (m_Validations)
		{
			PopulateDebugMessengerCreateInfo(dci);

			COSMOS_ASSERT(CreateDebugUtilsMessengerEXT(m_Instance, &dci, nullptr, &m_DebugMessenger) == VK_SUCCESS, "Failed to create Vulkan DebugUtilsMessenger");
		}
	}

	VKInstance::~VKInstance()
	{
		if (m_Validations) DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
	}

	std::vector<const char*> VKInstance::GetRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = m_Window->GetRequiredExtensions(glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (m_Validations) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensions;
	}

	bool VKInstance::CheckValidationLayersSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_ValidationsLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound) return false;
		}

		return true;
	}

	void VKInstance::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& ci)
	{
		ci = {};
		ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		ci.pNext = nullptr;
		ci.flags = 0;
		ci.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		ci.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		ci.pfnUserCallback = DebugCallback;
		ci.pUserData = nullptr;
	}
}

namespace Cosmos
{
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

		if (func != nullptr) return func(instance, pCreateInfo, pAllocator, pDebugMessenger);

		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

		if (func != nullptr) func(instance, debugMessenger, pAllocator);
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			COSMOS_WARN("Validation Layer: %s", pCallbackData->pMessage);
		}

		return VK_FALSE;
	}
}
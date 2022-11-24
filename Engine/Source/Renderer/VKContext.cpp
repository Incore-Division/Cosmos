#include "VKContext.h"

namespace Cosmos
{
	VKContext::VKContext(SharedRef<Window>& window, bool validations)
		: m_Window(window)
	{
		COSMOS_TRACE("Creating Renderer Context");

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		COSMOS_TRACE("%d extensions supported", extensionCount);

		m_Instance = std::make_shared<VKInstance>(m_Window, true);
		m_Device = std::make_shared<VKDevice>(m_Window, m_Instance);
	}

	VKContext::~VKContext()
	{

	}
}
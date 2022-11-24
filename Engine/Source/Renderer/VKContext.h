#pragma once

#include <vector>

#include "Core/Window.h"

#include "VKInstance.h"
#include "VKDevice.h"

namespace Cosmos
{
	class VKContext
	{
	public:

		// constructor
		VKContext(SharedRef<Window>& window, bool validations = true);

		// destructor
		~VKContext();

	private:

		SharedRef<Window>& m_Window;
		SharedRef<VKInstance> m_Instance;
		SharedRef<VKDevice> m_Device;
	};
}
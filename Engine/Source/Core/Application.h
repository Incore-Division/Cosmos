#pragma once

#include "Window.h"

#include "Renderer/VKContext.h"

#include "Util/Memory.h"
#include "Util/Logger.h"

namespace Cosmos
{
	class Application
	{
	public:

		// constructor
		Application();

		// destructor
		~Application();

	public:

		// main loop
		void Run();

	private:

		SharedRef<Window> m_Window;
		SharedRef<VKContext> m_Context;
	};
}
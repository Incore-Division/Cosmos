#include "Application.h"

namespace Cosmos
{
	Application::Application()
	{
		COSMOS_TRACE("Creating Application");

		m_Window = std::make_shared<Window>("Vulkan Renderer", 800, 600);
		m_Context = std::make_shared<VKContext>(m_Window, true);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (!m_Window->ShouldClose())
		{
			m_Window->Update();
		}
	}
}
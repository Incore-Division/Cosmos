#include "Window.h"

namespace Cosmos
{
	Window::Window(const char* title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		COSMOS_TRACE("Creating Window");

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
		COSMOS_ASSERT(m_Window != nullptr, "Failed to create Window");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
	}
}
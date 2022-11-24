#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Util/Memory.h"
#include "Util/Logger.h"

namespace Cosmos
{
	class Window
	{
	public:

		// constructor
		Window(const char* title, int width, int height);

		// destructor
		~Window();

		// returns the native window object
		inline GLFWwindow* GetNativeWindow() { return m_Window;  }

	public:

		// returns the window's title
		inline const char* GetTitle() { return m_Title; }

		// returns the required extensions by glfw
		inline const char** GetRequiredExtensions(uint32_t& count) { return glfwGetRequiredInstanceExtensions(&count); }

	public:

		// updates screen
		void Update();

		// returns if the window should be closed
		inline bool ShouldClose() { return glfwWindowShouldClose(m_Window); };

	private:

		GLFWwindow* m_Window;
		const char* m_Title;
		int m_Width;
		int m_Height;
	};
}
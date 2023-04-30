#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
static bool sGLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

IWindow* IWindow::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::Init(const WindowProps& props)
{
	mData.Title = props.Title;
	mData.Width = props.Width;
	mData.Height = props.Height;

	HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	if (!sGLFWInitialized)
	{
		// TODO: glfwTerminate on system shtudown
		int success = glfwInit();
		HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);

		sGLFWInitialized = true;
	}

	mWindow = glfwCreateWindow(props.Width, props.Height, mData.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(mWindow);
	glfwSetWindowUserPointer(mWindow, &mData);
	SetVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int32_t width, int32_t height)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			data->Width = width;
			data->Height = height;

			WindowResizeEvent event(width, height);
			data->EventCallback(event);
		});
	
	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			WindowCloseEvent event;
			data->EventCallback(event);
		});
	
	glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
			}
		});

	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data->EventCallback(event);
					break;
				}
			}
		});
	
	glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data->EventCallback(event);
		});
	
	glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			HZ_CORE_ASSERT(data, "GLFW WindowData is null");

			MouseMovedEvent event((float)xPos, (float)yPos);
			data->EventCallback(event);
		});
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(mWindow);
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(mWindow);
}

void WindowsWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	mData.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
	return mData.VSync;
}
}
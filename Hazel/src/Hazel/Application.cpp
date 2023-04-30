#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{

Application::Application()
	: mWindow(std::unique_ptr<IWindow>(IWindow::Create()))
	, mRunning(true) {}

Application::~Application() {}

void Application::Run()
{
	while (mRunning)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		mWindow->OnUpdate();
	}
}
	
}

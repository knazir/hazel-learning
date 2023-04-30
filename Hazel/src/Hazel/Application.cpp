#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
Application::Application()
	: mWindow(std::unique_ptr<IWindow>(IWindow::Create()))
	, mRunning(true)
{
	mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

	HZ_CORE_TRACE("{0}", e);
}

void Application::Run()
{
	while (mRunning)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		mWindow->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	mRunning = false;
	return true;
}
	
}

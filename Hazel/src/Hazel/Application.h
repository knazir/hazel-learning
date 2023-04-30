#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

namespace Hazel
{
	
class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
	void OnEvent(Event& e);

private:
	bool OnWindowClose(WindowCloseEvent& e);

	std::unique_ptr<IWindow> mWindow;
	bool mRunning;
};

// To be defined in CLIENT
Application* CreateApplication();

}


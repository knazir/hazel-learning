#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel
{
	
class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();

private:
	std::unique_ptr<IWindow> mWindow;
	bool mRunning;
};

// To be defined in CLIENT
Application* CreateApplication();

}


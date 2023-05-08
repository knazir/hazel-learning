#pragma once

#include "Core.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Window.h"

namespace Hazel
{
	
class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

private:
	bool OnWindowClose(WindowCloseEvent& e);

	std::unique_ptr<IWindow> mWindow;
	bool mRunning;
	LayerStack mLayerStack;
};

// To be defined in CLIENT
Application* CreateApplication();

}


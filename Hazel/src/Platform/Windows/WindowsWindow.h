#pragma once

#include "Hazel/Window.h"

class GLFWwindow;

namespace Hazel
{
class WindowsWindow : public IWindow
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return mData.Width; }
	inline unsigned int GetHeight() const override { return mData.Height; }

	// Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();

	GLFWwindow* mWindow;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	WindowData mData;
};
}


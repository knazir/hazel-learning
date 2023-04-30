#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int32_t argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	int32_t a = 5;
	HZ_INFO("Hello! Var={0}", a);

	Hazel::Application* app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
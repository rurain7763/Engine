#ifndef ENTRY_H
#define ENTRY_H

#include "core/Application.h"
#include "debug/Instrumentation.h"

// To be defined in CLIENT
engine::Application* CreateApplication();

#ifdef PLATFORM_MAC
int main(int argc, char** argv) {
	EG_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	engine::Application* app = CreateApplication();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
	app->Run();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
	delete app;
	EG_PROFILE_END_SESSION();

	return 0;
}
#elif PLATFORM_WINDOWS
int main(int argc, char** argv) {
	EG_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	engine::Application* app = CreateApplication();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
	app->Run();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
	delete app;
	EG_PROFILE_END_SESSION();

	return 0;
}
#endif

#endif // ENTRY_H
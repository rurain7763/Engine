#ifndef ENTRY_H
#define ENTRY_H

#include "core/Application.h"

// To be defined in CLIENT
engine::Application* CreateApplication();

#ifdef PLATFORM_MAC
int main(int argc, char** argv) {
	engine::Application* app = CreateApplication();
	app->Run();
	app->Shutdown();
	delete app;
	return 0;
}
#elif PLATFORM_WINDOWS
int main(int argc, char** argv) {
	engine::Application* app = CreateApplication();
	app->Run();
	app->Shutdown();
	delete app;
	return 0;
}
#endif

#endif // ENTRY_H
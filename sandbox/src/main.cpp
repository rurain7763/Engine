#include "Entry.h"
#include "Sandbox.h"

engine::Application* CreateApplication() {
    return new Sandbox();
}


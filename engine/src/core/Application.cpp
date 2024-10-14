#include "pch.h"
#include "Application.h"
#include "Logger.h"

namespace engine {
    Application::Application() {
        Logger::init();
        LOG_EG_INFO("Created application");
    }

    Application::~Application() {
    }

    void Application::Run() {
        
    }
}
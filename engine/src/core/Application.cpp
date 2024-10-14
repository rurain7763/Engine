#include "Application.h"
#include "Logger.h"

#include "pch.h"

namespace engine {
    Application::Application() {
        Logger::init();
        LOG_EG_INFO("Created application");
    }

    Application::~Application() {
    }

    void Application::Run() {
        
    }
};
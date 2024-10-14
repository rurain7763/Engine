#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"
#include "Windows.h"

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();

    private:
        std::unique_ptr<Windows> _window;
    };
};

#endif // APPLICATION_H
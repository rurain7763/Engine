#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    };
};

#endif // APPLICATION_H
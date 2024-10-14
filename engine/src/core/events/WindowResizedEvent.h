#ifndef WINDOWRESIZEDEVENT_H
#define WINDOWRESIZEDEVENT_H

#include "EngineHeader.h"
#include "../eventbus/Event.h"

namespace engine {
    class WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(int x, int y) : _x(x), _y(y) {}

        inline int GetX() const { return _x; }
        inline int GetY() const { return _y; }

        std::string ToString() const {
            return "WindowResizedEvent: x = " + std::to_string(_x) + " y = " + std::to_string(_y);
        }

    private:
        int _x, _y;
    };
}

#endif
#ifndef MOUSESCROLLEDEVENT_H
#define MOUSESCROLLEDEVENT_H

#include "EngineHeader.h"
#include "Event.h"

namespace engine {
    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(double& x, double& y) : _x(x), _y(y) {}

        inline double GetX() const { return _x; }
        inline double GetY() const { return _y; }

        std::string ToString() const {
            return "MouseScrolledEvent: ";
        }

    private:
        double _x, _y;
    };
}

#endif
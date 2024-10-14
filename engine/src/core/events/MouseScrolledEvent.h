#ifndef MOUSESCROLLEDEVENT_H
#define MOUSESCROLLEDEVENT_H

#include "EngineHeader.h"
#include "../eventbus/Event.h"

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x, int y) : _x(x), _y(y) {}

    inline int GetX() const { return _x; }
    inline int GetY() const { return _y; }

    std::string ToString() const {
        return "MouseScrolledEvent: ";
    }

private:
    float _x, _y;
};

#endif
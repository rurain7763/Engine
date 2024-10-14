#ifndef MOUSEMOVEDEVENT_H
#define MOUSEMOVEDEVENT_H

#include "EngineHeader.h"
#include "../eventbus/Event.h"

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(int x, int y) : _x(x), _y(y) {}

    inline int GetX() const { return _x; }
    inline int GetY() const { return _y; }

    std::string ToString() const {
        return "MouseMovedEvent: ";
    }

private:
    int _x, _y;
};

#endif
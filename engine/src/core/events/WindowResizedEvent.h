#ifndef WINDOWRESIZEDEVENT_H
#define WINDOWRESIZEDEVENT_H

#include "EngineHeader.h"
#include "../eventbus/Event.h"

namespace engine {
    class WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(int width, int height) : _width(width), _height(height) {}

        inline int GetWidth() const { return _width; }
        inline int GetHeight() const { return _height; }

        std::string ToString() const {
            return "WindowResizedEvent: x = " + std::to_string(_width) + " y = " + std::to_string(_height);
        }

    private:
        int _width, _height;
    };
}

#endif
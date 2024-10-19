#ifndef MOUSEBUTTONRELEASEDEVENT_H
#define MOUSEBUTTONRELEASEDEVENT_H

#include "EngineHeader.h"
#include "Event.h"

namespace engine {
    class MouseButtonReleasedEvent : public Event {
    public:
        MouseButtonReleasedEvent(int key) : _key(key) {}

        inline int GetKey() const { return _key; }

        std::string ToString() const {
            return "MouseButtonReleasedEvent: " + std::to_string(_key);
        }

    private:
        int _key;
    };
}

#endif
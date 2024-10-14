#ifndef MOUSEBUTTONPRESSEDEVENT_H
#define MOUSEBUTTONPRESSEDEVENT_H

#include "EngineHeader.h"
#include "../eventbus/Event.h"

namespace engine {
    class MouseButtonPressedEvent : public Event {
    public:
        MouseButtonPressedEvent(int key) : _key(key) {}

        inline int GetKey() const { return _key; }

        std::string ToString() const {
            return "MouseButtonPressedEvent: " + std::to_string(_key);
        }

    private:
        int _key;
    };
}

#endif
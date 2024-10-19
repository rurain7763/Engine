#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "EngineHeader.h"
#include "Event.h"

namespace engine {
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(int key) : _key(key) {}

        inline int GetKey() const { return _key; }

        std::string ToString() const {
            return "KeyPressedEvent: " + std::to_string(_key);
        }

    private:
        int _key;
    };
}

#endif
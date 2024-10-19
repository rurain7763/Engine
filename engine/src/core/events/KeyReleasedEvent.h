#ifndef KEYRELEASEDEVENT_H
#define KEYRELEASEDEVENT_H

#include "EngineHeader.h"
#include "Event.h"

namespace engine {
    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(int key) : _key(key) {}

        inline int GetKey() const { return _key; }

        std::string ToString() const {
            return "KeyReleasedEvent: " + std::to_string(_key);
        }

    private:
        int _key;
    };
}

#endif
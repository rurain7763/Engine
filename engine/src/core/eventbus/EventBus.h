#ifndef EVETBUS_H
#define EVETBUS_H

#include "EngineHeader.h"
#include "Event.h"

namespace engine {
    class IEventHandler {
    public:
        virtual ~IEventHandler() = default;

        virtual void HandleEvent(Event& event) = 0;
        virtual bool Equals(void* owner) = 0;
    };

    template<typename TOwner, typename TEvent>
    class EventHandler : public IEventHandler {
    private:
        typedef void (TOwner::*EventHandlerFunction)(TEvent&);

    public:
        ~EventHandler() = default;

        EventHandler(TOwner* owner, EventHandlerFunction handler) : _owner(owner), _handler(handler) {}

        virtual void HandleEvent(Event& event) override {
            TEvent& castedEvent = static_cast<TEvent&>(event);
            std::invoke(_handler, _owner, castedEvent);
        }

        virtual bool Equals(void* owner) override {
            TOwner* otherOwner = static_cast<TOwner*>(owner);
            return otherOwner == _owner;
        }

    private:
        TOwner* _owner;
        EventHandlerFunction _handler;
    };

    typedef std::vector<std::unique_ptr<IEventHandler>> EventHandlerList;

    class EG_API EventBus {
    public:
        EventBus() = default;
        virtual ~EventBus() = default;

        template<typename TOwner, typename TEvent>
        void Subscribe(TOwner* owner, void (TOwner::*handler)(TEvent&)) {
            std::type_index eventType = std::type_index(typeid(Event));
            auto eventHandler = std::make_unique<EventHandler<TOwner, TEvent>>(owner, handler);
            if(_eventHandlers.find(eventType) == _eventHandlers.end()) {
                _eventHandlers[eventType] = EventHandlerList();
            }
            _eventHandlers[eventType].push_back(std::move(eventHandler));
        }

        template<typename TOwner, typename TEvent>
        void Unsubscribe(TOwner* owner, void (TOwner::*handler)(TEvent&)) {
            std::type_index eventType = std::type_index(typeid(TEvent));
            auto pair = _eventHandlers.find(eventType);
            if(pair == _eventHandlers.end()) {
                return;
            }
            // this is a bit of a hack, but it works
            // so maybe future me can come up with a better solution
            for(auto& eventHandler : pair->second) {
                if(eventHandler->Equals(owner)) {
                    swap(eventHandler, pair->second.back());
                    return;
                }
            }

            if(pair->second.empty()) {
                _eventHandlers.erase(eventType);
            }
        }

        template<typename TEvent, typename ...TArgs>
        void Publish(TArgs&&... args) {
            std::type_index eventType = std::type_index(typeid(TEvent));
            auto pair = _eventHandlers.find(eventType);
            if(pair == _eventHandlers.end()) {
                return;
            }
            for(auto& eventHandler : pair->second) {
                TEvent event(std::forward<TArgs>(args)...);
                eventHandler->HandleEvent(event);
            }
        }

    private:
        std::unordered_map<std::type_index, EventHandlerList> _eventHandlers;
    };
}

#endif
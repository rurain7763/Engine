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

        EventHandler& operator=(const EventHandler& other) {
            _owner = other._owner;
			_handler = other._handler;
			return *this;
        }

    private:
        TOwner* _owner;
        EventHandlerFunction _handler;
    };

    typedef std::list<IEventHandler*> EventHandlerList;

    class EventBus {
    public:
        EventBus() = default;
        virtual ~EventBus() {
            for (auto& pair : _eventHandlers) {
                for (auto& eventHandler : pair.second) {
                    delete eventHandler;
                }
            }
            _eventHandlers.clear();
        }

        template<typename TOwner, typename TEvent>
        void Subscribe(TOwner* owner, void (TOwner::*handler)(TEvent&)) {
            std::type_index eventType = std::type_index(typeid(TEvent));
            auto eventHandler = new EventHandler<TOwner, TEvent>(owner, handler);
            _eventHandlers[eventType].push_back(eventHandler);
        }

        template<typename TOwner, typename TEvent>
        void Unsubscribe(TOwner* owner) {
			std::type_index eventType = std::type_index(typeid(Event));
			auto pair = _eventHandlers.find(eventType);
			if(pair == _eventHandlers.end()) {
				return;
			}
			auto& eventHandlers = pair->second;
			for(auto it = eventHandlers.begin(); it != eventHandlers.end(); ++it) {
				if((*it)->Equals(owner)) {
					delete *it;
					eventHandlers.erase(it);
					break;
				}
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
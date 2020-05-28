// Event manager singleton

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "Event.hpp"


namespace Veri {
class EventManager {
    public:
        // Disallows copying
        EventManager(EventManager const&) = delete;
        EventManager& operator=(EventManager const&) = delete;

        // Disallows moving
        EventManager(EventManager&&) noexcept = delete;
        EventManager& operator=(EventManager&&) noexcept = delete;

        // Gets a threads-safe instance
        static EventManager& GetInstance();

        void AddEvent(std::shared_ptr<Event> evntPtr);
        void RemoveEvent(std::shared_ptr<Event> evntPtr);

        void PollEvents(sf::RenderWindow& window);

        
    private:
        EventManager() = default;
        ~EventManager() = default;

    private:
        std::unordered_map<Type, std::vector<std::shared_ptr<Event>>> m_Events;
    };
}
// Event interface

#pragma once

#include <SFML/Graphics.hpp>


namespace Veri {
    using Type = sf::Event::EventType;
    
    class Event {
    public:
        virtual ~Event() = default;

        virtual void OnEvent(sf::Event& evnt) = 0;
        virtual Type GetType() const = 0;
    };
}
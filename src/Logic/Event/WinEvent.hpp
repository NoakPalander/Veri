#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace Veri {
    using Type = sf::Event::EventType;

    class WinEvent : public Event {
    public:
        using Callback = std::function<void(void)>;

        WinEvent(Type type, Callback const& callback);
        ~WinEvent() = default;

        virtual void OnEvent(sf::Event& evnt) override;
        virtual inline Type GetType() const override { 
            return m_Type; 
        }

        static inline decltype(auto) MakeEvent(Type type, Callback const& callback) {
            return std::make_shared<WinEvent>(type, callback);
        }

    private:
        Type m_Type;
        Callback m_Callback;
    };
}
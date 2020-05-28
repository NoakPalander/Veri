#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>


namespace Veri {
    class MwEvent : public Event {
    public:
        using Wheel = sf::Event::MouseWheelEvent;
        using Type = sf::Event::EventType;
        using Callback = std::function<void(Wheel)>;

        explicit MwEvent(Type type, Callback const& callback);
        ~MwEvent() = default;

        virtual void OnEvent(sf::Event& event) override;

        virtual inline Type GetType() const override {
            return m_Type;
        }

        static inline decltype(auto) WheelHook(Wheel wheel, Callback const& func) {
            return std::make_pair(wheel, func);
        }

        static inline decltype(auto) MakeEvent(Type type, Callback const& callback) {
            return std::make_shared<MwEvent>(type, callback);
        }

    private:
        Type m_Type;
        Callback m_Callback;
    };
}
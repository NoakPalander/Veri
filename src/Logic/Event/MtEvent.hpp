// Motion event

#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>


namespace Veri {
    class MtEvent : public Event {
    public:
        using Move = sf::Event::MouseMoveEvent;
        using Callback = std::function<void(Move)>;
        
        explicit MtEvent(Type type, Callback const& callback);
        ~MtEvent() = default;

        virtual void OnEvent(sf::Event& event) override;

        virtual inline Type GetType() const override {
            return m_Type;
        }

        static inline decltype(auto) MakeEvent(Type type, Callback const& callback) {
            return std::make_shared<MtEvent>(type, callback);
        }

    private:
        Type m_Type;
        Callback m_Callback;
    };
}
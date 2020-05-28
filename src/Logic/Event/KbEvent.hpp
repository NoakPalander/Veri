// Keyboard event

#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <functional>


namespace Veri {
    class KbEvent : public Event {
    public:
        using Key = sf::Keyboard::Key;
        using Callback = std::function<void(void)>;
        using Hooks = std::unordered_map<Key, Callback>;

        KbEvent(Type type, Hooks const& hooks);
        ~KbEvent() = default;

        virtual void OnEvent(sf::Event& event) override;
        
        virtual inline Type GetType() const override { 
            return m_Type; 
        }

        static inline decltype(auto) KeyHook(Key key, Callback const& func) {
            return std::make_pair(key, func);
        }

        static inline decltype(auto) MakeEvent(Type type, Hooks const& hooks) {
            return std::make_shared<KbEvent>(type, hooks);
        }

    private:
        Type m_Type;
        Hooks m_Hooks;
    };
}
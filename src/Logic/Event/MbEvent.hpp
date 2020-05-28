// Mouse button event

#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <functional>


namespace Veri {
    class MbEvent : public Event {
    public:
        using Button = sf::Mouse::Button;
        using Callback = std::function<void(void)>;
        using Hooks = std::unordered_map<Button, Callback>;

        explicit MbEvent(Type type, Hooks const& hooks);
        ~MbEvent() = default;

        virtual void OnEvent(sf::Event& evnt) override;

        virtual inline Type GetType() const override {
            return m_Type;
        }

        static inline decltype(auto) ButtonHook(Button btn, Callback const& func) {
            return std::make_pair(btn, func);
        }

        static inline decltype(auto) MakeEvent(Type type, Hooks const& hooks) {
            return std::make_shared<MbEvent>(type, hooks);
        }

    private:
        Type m_Type;
        Hooks m_Hooks;
    };
}
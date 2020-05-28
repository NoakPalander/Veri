#include "MbEvent.hpp"


namespace Veri {
    MbEvent::MbEvent(Type type, Hooks const& hooks)
        :   m_Type{type}, m_Hooks{hooks}
    {
    }


    /*virtual*/ void MbEvent::OnEvent(sf::Event& event) /*override*/ {
        if (auto callback = m_Hooks[event.mouseButton.button]; callback != nullptr)
            callback();
    }
}
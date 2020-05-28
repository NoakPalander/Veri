#include "KbEvent.hpp"


namespace Veri {
    KbEvent::KbEvent(Type type, Hooks const& hooks) 
        :   m_Type(type), m_Hooks(hooks)
    {
    }


    /*virtual*/ void KbEvent::OnEvent(sf::Event& event) /* override */ {
        if (auto callback = m_Hooks[event.key.code]; callback != nullptr)
            callback();
    }
}
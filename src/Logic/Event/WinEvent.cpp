#include "WinEvent.hpp"


namespace Veri {
    WinEvent::WinEvent(Type type, Callback const& callback)
        :   m_Type(type), m_Callback(callback)
    {
    }


    /*virtual*/ void WinEvent::OnEvent(sf::Event& evnt) /*override*/ {
        if (evnt.type == m_Type)
            m_Callback();
    }
}
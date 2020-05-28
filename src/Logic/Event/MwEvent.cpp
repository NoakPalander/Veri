#include "MwEvent.hpp"


namespace Veri {
    MwEvent::MwEvent(Type type, Callback const& callback)
        :   m_Type{type}, m_Callback{callback} 
    {
    }

    /*virtual*/ void MwEvent::OnEvent(sf::Event& event) /*override*/ {
        m_Callback(event.mouseWheel);  
    }
}
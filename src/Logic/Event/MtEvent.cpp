#include "MtEvent.hpp"


namespace Veri {
    MtEvent::MtEvent(Type type, Callback const& callback) 
        :   m_Type{type}, m_Callback{callback}
    {}


    /*virtual*/ void MtEvent::OnEvent(sf::Event& event) /*override*/ {
        m_Callback(event.mouseMove);
    }
}
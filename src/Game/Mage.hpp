#pragma once

#include "../Logic/Event/Event.hpp"
#include "../Logic/Event/EventManager.hpp"
#include "../Logic/Event/KbEvent.hpp"
#include "../Logic/AudioPlayer.hpp"
#include "../Graphics/Character.hpp"
#include "../Graphics/Rectangle.hpp"
#include "Cast.hpp"
#include "Cooldowns.hpp"
#include <memory>
#include <SFML/Graphics.hpp>


namespace Veri {
    class Mage : public Character {
    public:
        explicit Mage(uint sceneWidth, sf::Vector2f const& position, sf::Vector2f const& size = { 150.f, 150.f }, float switchTime = 0.3f);
        ~Mage();

        Mage(Mage&& other) noexcept;

        void Init();

        virtual void Update(float deltaTime) override;
        virtual void Draw(sf::RenderWindow& window) override;

        void RemoveThunder(bool proc = false);
        void RemoveFire(bool proc = false);
        
        inline Rectangle GetThunder() const { return m_Thunder.cast; }
        inline Rectangle GetFire()    const { return m_Fire.cast;    }
        inline Rectangle GetArcane()  const { return m_Arcane.cast;  }
        inline Cast* GetCast() {
            if (m_Thunder.isCasted || m_Thunder.isCasting)
                return &m_Thunder;
            
            else if (m_Fire.isCasted || m_Fire.isCasting)
                return &m_Fire;
        
            else if (m_Arcane.isCasted || m_Arcane.isCasting)
                return &m_Arcane;
            
            return nullptr;
        }

    private:
        uint m_SceneWidth;
        sf::Vector2f m_Position;
        sf::Vector2f m_Size;

        std::shared_ptr<Event> m_KeyPressEvents;
        std::shared_ptr<Event> m_KeyReleaseEvents;
        
        Cast m_Thunder, m_ThunderCloud, m_Fire, m_Shield, m_Arcane;

        Cooldowns m_Cooldowns;
        AudioPlayer m_Audio;
    };
}
#pragma once

#include <SFML/Graphics.hpp>
#include "../Logic/Collider.hpp"
#include <memory>

namespace Veri {
    class Rectangle {
    public:
        Rectangle(sf::Vector2f const& size, sf::Vector2f const& position, std::string const& filename = "",
                        sf::Color color = sf::Color::Black);
        
        Rectangle(Rectangle const&) = default;
        Rectangle(Rectangle&& other) noexcept;
        
        Rectangle();
        ~Rectangle() = default;

        Rectangle& operator=(Rectangle const&) = default;
        Rectangle& operator=(Rectangle&& other) noexcept;

        void SetColor(sf::Color const& color);
        void SetPosition(sf::Vector2f const& pos);
        void SetTextureRect(sf::IntRect const& uvRect);
        void SetPushBack(float push);

        void Draw(sf::RenderWindow& window) const;
        void Move(sf::Vector2f const& offset);
        void Rotate(float angle);
        
        inline Collider     GetCollider()       { return Collider(m_Body); }
        inline sf::Texture& GetTexture()        { return *m_Texture.get(); }
        inline sf::Vector2f GetPosition() const { return m_Body.getPosition(); }
        inline float        GetPushBack() const { return m_PushBack; }

    private:
        sf::RectangleShape m_Body;
        std::shared_ptr<sf::Texture> m_Texture;
        float m_PushBack;
    };
}
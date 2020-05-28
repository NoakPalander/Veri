#pragma once

#include <SFML/Graphics.hpp>

namespace Veri {
    class Collider {
    public:
        Collider(sf::RectangleShape& body);
        ~Collider() = default;

        void Move(float dx, float dy);
        bool CheckCollision(Collider other, sf::Vector2f& direction, float push);
        
        inline sf::Vector2f GetPosition() const { return m_Body.getPosition(); }
        inline sf::Vector2f GetHalfSize() const { return m_Body.getSize() / 2.f; }

    private:
        sf::RectangleShape& m_Body;
    };
}
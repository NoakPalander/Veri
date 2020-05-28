#include "Collider.hpp"
#include <cmath>


namespace Veri {
    Collider::Collider(sf::RectangleShape& body) 
        :   m_Body(body) 
    {
    }


    void Collider::Move(float dx, float dy) {
        m_Body.move(dx, dy);
    }


    bool Collider::CheckCollision(Collider other, sf::Vector2f& direction, float push) {
        sf::Vector2f const otherPos      = other.GetPosition();
        sf::Vector2f const otherHalfSize = other.GetHalfSize();
        sf::Vector2f const thisPos       = this->GetPosition();
        sf::Vector2f const thisHalfSize  = this->GetHalfSize();

        float const deltaX = otherPos.x - thisPos.x;
        float const deltaY = otherPos.y - thisPos.y;

        float const intersectX = std::abs(deltaX) - otherHalfSize.x - thisHalfSize.x;
        float const intersectY = std::abs(deltaY) - otherHalfSize.y - thisHalfSize.y;

        // We have a collision
        if (intersectX < 0.f && intersectY < 0.f) {
            // Clamps push to [0 to 1]
            push = std::min(std::max(push, 0.f), 1.f);

            if (intersectX > intersectY) {
                if (deltaX > 0.f) {
                    Move(intersectX * (1.f - push), 0.f);
                    other.Move(-intersectX * push, 0.f);

                    direction.x = 1.f;
                    direction.y = 0.f;
                }
                else {
                    Move(-intersectX * (1.f - push), 0.f);
                    other.Move(intersectX * push, 0.f);

                    direction.x = -1.f;
                    direction.y = 0.f;
                }
            }
            else {
                if (deltaY > 0.f) {
                    Move(0.f, intersectY * (1.f - push));
                    other.Move(0.f, -intersectY * push);
                    
                    direction.x = 0.f;
                    direction.y = 1.f;
                }
                else {
                    Move(0.f, -intersectY * (1.f - push));
                    other.Move(0.f, intersectY * push);
                
                    direction.x = 0.f;
                    direction.y = -1.f;
                }
            }

            return true;
        }

        return false;   
    }
}
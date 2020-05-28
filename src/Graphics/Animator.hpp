#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Veri {
    class Animator {
    public:
        Animator(sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
        ~Animator() = default;

        uint Update(float deltaTime);

        void SetTexture();
        void SetUVRect(sf::IntRect const& uvRect);
        void SetIndecies(std::vector<sf::Vector2u> const& indices);
        void SetFacing(bool isFacingRight);

        inline sf::IntRect               GetUVRect()     const { return m_UVRect;       }
        inline std::vector<sf::Vector2u> GetIndices()    const { return m_Indices;      }
        inline bool                      IsFacingLeft()  const { return m_IsFacingLeft; } 

    private:
        sf::Vector2u m_ImageCount, m_CurrentImage;
        float m_TotalTime, m_SwitchTime;
        sf::IntRect m_UVRect;

        std::vector<sf::Vector2u> m_Indices;
        uint m_Index;

        bool m_IsFacingLeft;
    };
}
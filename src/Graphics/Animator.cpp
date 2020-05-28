#include "Animator.hpp"
#include "../Logic/Logger.hpp"


namespace Veri {
    Animator::Animator(sf::Texture& texture, sf::Vector2u imageCount, float switchTime)
        :    m_ImageCount{imageCount}, m_SwitchTime{switchTime}, m_TotalTime{}, m_Index{} {

        m_UVRect.width = texture.getSize().x / static_cast<float>(imageCount.x);
        m_UVRect.height = texture.getSize().y / static_cast<float>(imageCount.y);
    }


    void Animator::SetIndecies(std::vector<sf::Vector2u> const& indices) {
        if (m_Indices != indices)
            m_Index = 0;
            
        m_Indices = indices;
    }


    void Animator::SetFacing(bool isFacingLeft) {
        m_IsFacingLeft = isFacingLeft;
    }


    uint Animator::Update(float deltaTime) {    
        m_TotalTime += deltaTime;

        if (m_TotalTime >= m_SwitchTime) {
            m_TotalTime -= m_SwitchTime;

            // Crashes here, perhaps indecies aren't set properly
            m_CurrentImage.y = m_Indices[m_Index].y;
            m_CurrentImage.x = m_Indices[m_Index].x;

            m_Index = (m_Index == m_Indices.size() - 1) ? 0 : m_Index + 1;
        }

        m_UVRect.top = m_CurrentImage.y * m_UVRect.height;

        // Rotates the sprite either to the left or right (facing)
        if (m_IsFacingLeft) {
            m_UVRect.left = (m_CurrentImage.x + 1) * std::abs(m_UVRect.width);
            m_UVRect.width = -std::abs(m_UVRect.width);
        }
        else {
            m_UVRect.left = m_CurrentImage.x * m_UVRect.width;
            m_UVRect.width = std::abs(m_UVRect.width);
        }

        return m_Index; // returns the frame
    }


    void Animator::SetUVRect(sf::IntRect const& uvRect) {
        m_UVRect = uvRect;
    }
}
#pragma once

#include <SFML/Graphics.hpp>

namespace Veri {
    class Camera {
    public:
        Camera(sf::Vector2f const& center, sf::Vector2f const& size, float viewHeight);
        ~Camera() = default;

        void UpdateCenter(sf::Vector2f const& center);
        void OnResize(sf::Vector2u const& windowSize);
        void Zoom(float ratio);

        // Allows implicit convertion from Camera to sf::View
        
        inline operator     sf::View()             { return m_View; }
        inline float        GetAspectRatio() const { return m_AspectRatio; }
        inline sf::Vector2f GetCenter()      const { return m_Center; }
        inline sf::Vector2f GetSize()        const { return m_View.getSize(); }

    private:
        sf::Vector2f m_Center;
        sf::View m_View;
        float const m_ViewHeight;
        float m_AspectRatio;
    };
}
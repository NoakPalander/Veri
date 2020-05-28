#include "Camera.hpp"


namespace Veri {
    Camera::Camera(sf::Vector2f const& center, sf::Vector2f const& size, float viewHeight) 
        :   m_Center{center}, m_ViewHeight{viewHeight}, m_AspectRatio{static_cast<float>(size.x) / static_cast<float>(size.y)} {

        m_View.setCenter(center);
        m_View.setSize(size);
    }


    void Camera::UpdateCenter(sf::Vector2f const& center) {
        m_Center = center;
        m_View.setCenter(center);
    }


    void Camera::Zoom(float ratio) {
        m_View.zoom(ratio);
    }


    void Camera::OnResize(sf::Vector2u const& windowSize) {
        m_AspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        m_View.setSize(m_ViewHeight * m_AspectRatio, m_ViewHeight);
    }
}
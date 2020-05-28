#include "Rectangle.hpp"
#include "fmt/fmt.hpp"


namespace Veri {
    Rectangle::Rectangle(sf::Vector2f const& size, sf::Vector2f const& position, std::string const& filename, sf::Color color)
        :    m_Body{}, m_Texture{std::make_shared<sf::Texture>()}, m_PushBack{} {
            
        if (!filename.empty()) {
            if (!m_Texture->loadFromFile(filename)) {
                fmt::print("Failed to load resource {}!", filename);
                std::abort();
            }

            m_Body.setTexture(m_Texture.get());
        }    
        
        m_Body.setSize(size);
        m_Body.setOrigin(size / 2.f);
        m_Body.setPosition(position);
        m_Body.setFillColor(color);
    }

    Rectangle::Rectangle(Rectangle&& other) noexcept {
        if (&other != this) {
            m_Body      = std::move(other.m_Body);
            m_Texture   = std::move(other.m_Texture);
            m_PushBack  = std::move(other.m_PushBack);
        }
    }


    Rectangle::Rectangle()
        :   m_Body{}, m_Texture{}, m_PushBack{} {}


    Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
        if (&other != this) {
            m_Body      = std::move(other.m_Body);
            m_Texture   = std::move(other.m_Texture);
            m_PushBack  = std::move(other.m_PushBack);
        }

        return *this;
    }


    void Rectangle::SetColor(sf::Color const& color) {
        m_Body.setFillColor(color);
    }


    void Rectangle::SetPosition(sf::Vector2f const& pos) {
        m_Body.setPosition(pos);
    }


    void Rectangle::SetTextureRect(sf::IntRect const& uvRect) {
        m_Body.setTextureRect(uvRect);
    }


    void Rectangle::SetPushBack(float push) {
        m_PushBack = push;
    }


    void Rectangle::Draw(sf::RenderWindow& window) const {
        window.draw(m_Body);
    }


    void Rectangle::Move(sf::Vector2f const& offset) {
        m_Body.move(offset);
    }


    void Rectangle::Rotate(float angle) {
        m_Body.rotate(angle);
    }
}
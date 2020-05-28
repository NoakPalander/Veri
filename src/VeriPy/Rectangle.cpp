#include "Rectangle.hpp"


namespace VeriPy {
    Rectangle::Rectangle() 
        :   m_Filename{}, m_Size{}, m_Position{}, m_Color{ 0, 0, 0, 255 }
    {
    }


    void Rectangle::Create() {
        auto&[w, h] = m_Size;
        auto&[x, y] = m_Position;
        auto&[r, g, b, a] = m_Color;
        
        m_Rectangle = std::make_shared<Veri::Rectangle>(Veri::Rectangle{ { w, h }, { x, y}, m_Filename, sf::Color{ r, g, b, a} });
    }


    void Rectangle::SetFilename(std::string const& filename) {
        m_Filename = filename;
    }


    void Rectangle::SetSize(std::tuple<float, float> const& size) {
        m_Size = size;
    }
    
    
    void Rectangle::SetSize(float w, float h) {
        m_Size = std::make_tuple(w, h);
    }


    void Rectangle::SetPosition(std::tuple<float, float> const& position) {
        m_Position = position;
    }
    
    
    void Rectangle::SetPosition(float w, float h) {
        m_Position = std::make_tuple(w, h);
    }


    void Rectangle::SetColor(std::array<std::uint8_t, 4> const& color) {
        m_Color = color;
    }


    void Rectangle::SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
        m_Color = std::array{ r, g, b, a };
    }
}
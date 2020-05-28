#include "Cast.hpp"


namespace VeriPy {
    Cast::Cast() 
        :   m_Filename{}, m_Animation{}, m_Color{}, m_IsRight{}, m_Position{}, m_Cast{}
    {
    }


    void Cast::Create() {
        auto&[x, y] = m_Position;
        auto&[w, h] = m_Size;
        auto&[r, g, b, a] = m_Color;

        Veri::Cast temp{};
        temp.cast = Veri::Rectangle{ { w, h }, { x, y }, m_Filename, sf::Color{ r, g, b, a } };
        temp.isCasted = false;
        temp.isCasting = false;
        
        std::vector<sf::Vector2u> out;
        out.reserve(m_Animation.size());

        for (auto&[xPos, yPos] : m_Animation)
            out.emplace_back(sf::Vector2u{xPos, yPos});
        
        temp.animation = out;
        m_Cast = std::make_shared<Veri::Cast>(std::move(temp));
    }


    void Cast::SetFilename(std::string const& filename) {
        m_Filename = filename;
    }

    
    void Cast::SetAnimation(std::vector<std::tuple<uint, uint>> const& animation) {
        m_Animation = animation;
    }

    
    void Cast::SetColor(std::array<std::uint8_t, 4> const& color) {
        m_Color = color;
    }


    void Cast::SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
        m_Color = std::array{ r, g, b, a };
    }    
    
    void Cast::SetDirection(bool isRight) {
        m_IsRight = isRight;
    }


    void Cast::SetPosition(std::tuple<float, float> const& position) {
        m_Position = position;
    }


    void Cast::SetPosition(float x, float y) {
        m_Position = std::make_tuple(x, y);
    }


    void Cast::SetSize(std::tuple<float, float> const& size) {
        m_Size = size;
    }


    void Cast::SetSize(float w, float h) {
        m_Size = std::make_tuple(w, h);
    }
}
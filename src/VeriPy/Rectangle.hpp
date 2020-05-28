#pragma once

#include "../Graphics/Rectangle.hpp"
#include <tuple>
#include <string>

namespace VeriPy {
    class Rectangle : public std::enable_shared_from_this<Rectangle> {
    public:
        std::shared_ptr<Rectangle> getptr() { return shared_from_this(); }

        Rectangle();
        ~Rectangle() = default;

        void Create();

        void SetFilename(std::string const& filename);

        void SetSize(std::tuple<float, float> const& size);
        void SetSize(float w, float h);

        void SetPosition(std::tuple<float, float> const& position);
        void SetPosition(float w, float h);

        void SetColor(std::array<std::uint8_t, 4> const& color);
        void SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

        inline std::tuple<float, float>    GetSize()     const { return m_Size;      }
        inline std::tuple<float, float>    GetPosition() const { return m_Position;  }
        inline std::array<std::uint8_t, 4> GetColor()    const { return m_Color;     }
        inline std::shared_ptr<Veri::Rectangle> GetRectangle() { return m_Rectangle; }

    private:
        std::string m_Filename;

        std::tuple<float, float> m_Size;
        std::tuple<float, float> m_Position;
        std::array<std::uint8_t, 4> m_Color;

        std::shared_ptr<Veri::Rectangle> m_Rectangle;
    };
}
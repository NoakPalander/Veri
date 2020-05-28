#pragma once

#include "../Game/Cast.hpp"
#include <array>
#include <tuple>
#include <vector>
#include <string>
#include <memory>

namespace VeriPy {
    class Cast : public std::enable_shared_from_this<Cast> {
    public:
        std::shared_ptr<Cast> getptr() { return shared_from_this(); }

        Cast();
        ~Cast() = default;

        void Create();
        
        /* Setters */
        void SetFilename(std::string const& filename);
        void SetAnimation(std::vector<std::tuple<uint, uint>> const& animation);
        void SetColor(std::array<std::uint8_t, 4> const& color);
        void SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

        void SetDirection(bool isRight);

        void SetPosition(std::tuple<float, float> const& position);
        void SetPosition(float x, float y);

        void SetSize(std::tuple<float, float> const& size);
        void SetSize(float w, float h);

        /* Getters */
        inline std::vector<std::tuple<uint, uint>> GetAnimation() const { return m_Animation; }
        inline std::array<std::uint8_t, 4>         GetColor()     const { return m_Color;     }
        inline bool                                GetDirection() const { return m_IsRight;   }
        inline std::tuple<float, float>            GetSize()      const { return m_Size;      }
        inline std::tuple<float, float>            GetPosition()  const { return m_Position;  }
        inline std::shared_ptr<Veri::Cast>         GetCast()            { return m_Cast; }

    private:
        std::string m_Filename;
        std::vector<std::tuple<uint, uint>> m_Animation;
        std::array<std::uint8_t, 4> m_Color;
        bool m_IsRight;

        std::tuple<float, float> m_Size, m_Position;

        std::shared_ptr<Veri::Cast> m_Cast;
    };
}
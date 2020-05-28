#pragma once

#include "../Graphics/Rectangle.hpp"
#include <vector>

namespace Veri {
    struct Cast {
        Cast(Rectangle cast, bool isCasting, bool isCasted, bool isRight = true, std::vector<sf::Vector2u> animation = {}) 
            :   cast{cast}, isCasting{isCasting}, isCasted{isCasted}, isRight{isRight}, animation(animation) {}

        Cast() = default;
        ~Cast() = default;

        Cast(Cast&& other) noexcept {
            if (&other != this) {
                cast        = std::move(other.cast);
                isCasting   = std::move(other.isCasting);
                isCasted    = std::move(other.isCasted);
                isRight     = std::move(other.isRight);
                animation   = std::move(other.animation);
            }
        }

        Cast& operator=(Cast&& other) noexcept {
            if (&other != this) {
                cast        = std::move(other.cast);
                isCasting   = std::move(other.isCasting);
                isCasted    = std::move(other.isCasted);
                isRight     = std::move(other.isRight);
                animation   = std::move(other.animation);
            }

            return *this;
        }

        Rectangle cast{};
        bool isCasting{};
        bool isCasted{};
        bool isRight{};
        std::vector<sf::Vector2u> animation{};
    };
}
#pragma once

#include "../Game/Mage.hpp"
#include "../Graphics/Character.hpp"
#include "Rectangle.hpp"
#include <memory>
#include <tuple>
#include <functional>

namespace VeriPy {
    class Player : public std::enable_shared_from_this<Player> {
    public:
        std::shared_ptr<Player> getptr() { return shared_from_this(); }

        Player(std::tuple<float, float> const& position, uint sceneWidth);

        Player();
        ~Player() = default;

        void OnCastCollision(std::shared_ptr<VeriPy::Rectangle> rect, std::function<void(void)> const& action);
        void Create();

        void SetPosition(std::tuple<float, float> const& position);
        void SetPosition(float x, float y);

        void SetSceneWidth(uint sceneWidth);
        void SetSpeed(float speed);
        void SetFacingLeft(bool isFacingLeft);

        void RemoveCast();

        inline std::tuple<float, float> GetPosition() const { return m_Position; }
        inline std::shared_ptr<Veri::Character> GetPlayer() { return s_Player; }


    private:
        std::tuple<float, float> m_Position;
        uint m_SceneWidth;

        float m_Speed;
        inline static std::shared_ptr<Veri::Character> s_Player{};
    };
}
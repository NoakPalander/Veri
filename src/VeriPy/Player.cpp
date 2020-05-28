#include "Player.hpp"
#include "../Logic/Validator.hpp"
#include "../Logic/Logger.hpp"


namespace VeriPy {
    Player::Player(std::tuple<float, float> const& position, uint sceneWidth) 
        :   m_Position{position}, m_SceneWidth{sceneWidth}, m_Speed{ 150.f }
    {
    }

    Player::Player() 
        :   m_Position{}, m_SceneWidth{}, m_Speed{ 150.f }
    {
    }
 

    void Player::OnCastCollision(std::shared_ptr<VeriPy::Rectangle> rect, std::function<void(void)> const& action) {
        if (auto cast = dynamic_cast<Veri::Mage*>(s_Player.get())->GetCast(); cast != nullptr) {
            sf::Vector2f direction{};

            if (rect->GetRectangle()->GetCollider().CheckCollision(cast->cast.GetCollider(), direction, 1.f))           
                action();
        }
    }


    void Player::Create() {
        if (!isValid(s_Player)) {
            auto[x, y] = m_Position;
            s_Player = std::make_shared<Veri::Mage>(Veri::Mage(m_SceneWidth, { x, y }));
        }
    }


    void Player::SetSceneWidth(uint sceneWidth) {
        m_SceneWidth = sceneWidth;
    }


    void Player::SetSpeed(float speed) {
        m_Speed = speed;
    }


    void Player::SetPosition(std::tuple<float, float> const& position) {
        m_Position = position;
    }


    void Player::SetPosition(float x, float y) {
        m_Position = std::make_tuple(x, y);
    }


    void Player::SetFacingLeft(bool isFacingLeft) {
        valid(s_Player)->SetFacingLeft(isFacingLeft);
    }


    void Player::RemoveCast() {
        valid(s_Player)->RemoveCast();
    }
}
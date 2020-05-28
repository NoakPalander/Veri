#pragma once

#include "../Game/Cast.hpp"
#include "Animator.hpp"
#include "../Logic/Collider.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace Veri {
    class Character {
    public:
        explicit Character(std::string const& filename, sf::Vector2u const& imgCount, sf::Vector2f const& size, sf::Vector2f const& position, 
                    float speed, float jumpHeight, float switchTime, uint sceneWidth);
        
        Character();
        virtual ~Character() = default;

        void Init(std::string const& filename, sf::Vector2u const& imgCount, sf::Vector2f const& size, sf::Vector2f const& position, 
                    float speed, float jumpHeight, float switchTime, uint sceneWidth);

        void OnCollision(sf::Vector2f direction);
        virtual void Update(float deltaTime);
        virtual void Draw(sf::RenderWindow& window);

        void Hit(float damage);
        void RemoveCast();

        void SetIdle(std::vector<sf::Vector2u> const& animation);    
        void SetWalking(std::vector<sf::Vector2u> const& animation);
        void SetJumping(std::vector<sf::Vector2u> const& animation);    
        void SetDeath(std::vector<sf::Vector2u> const& animation);
        void SetCast(Cast* const cast);
        void SetVelocity(sf::Vector2f const& velocity);
        void SetFacingLeft(bool isFacingLeft);

        inline Collider     GetCollider()           { return Collider{m_Body}; }
        inline sf::Vector2f GetPosition()     const { return m_Body.getPosition(); }
        inline sf::Vector2f GetSize()         const { return m_Body.getSize(); }
        inline sf::Vector2f GetVelocity()     const { return m_Velocity; }
        inline bool         IsDead()          const { return m_IsDead; }
        inline bool         IsCasting()       const { return m_Cast != nullptr; }

    protected:
        bool m_CanJump;
        sf::Vector2f m_Velocity;
        std::shared_ptr<Animator> m_Animator;
        float m_JumpHeight;
        float m_SwitchTime;
        sf::RectangleShape m_Body;
        float m_Health;
        
        std::string m_Filename;
        sf::Vector2u m_ImgCount;
        sf::Vector2f m_Size;
        sf::Vector2f m_Position;
        float m_Speed;

    private:
        inline static sf::Texture s_Texture{};

        bool m_IsFaceLeft;
        std::vector<sf::Vector2u> m_IdleAnimation;
        std::vector<sf::Vector2u> m_WalkingAnimation;
        std::vector<sf::Vector2u> m_JumpingAnimation;
        std::vector<sf::Vector2u> m_DeathAnimation;
        uint m_SceneWidth;

        bool m_IsDead;
        Cast* m_Cast;
    };
}
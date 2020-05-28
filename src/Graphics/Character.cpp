#include "Character.hpp"
#include "fmt/fmt.hpp"
#include "../Logic/Event/KbEvent.hpp"
#include "../Logic/Event/EventManager.hpp"
#include "../Logic/Validator.hpp"
#include "../Logic/Logger.hpp"


namespace Veri {
    Character::Character(std::string const& filename, sf::Vector2u const& imgCount, sf::Vector2f const& size, sf::Vector2f const& position, 
                        float speed, float jumpHeight, float switchTime, uint sceneWidth) 
        
        :   m_IdleAnimation{}, m_WalkingAnimation{}, m_JumpingAnimation{}, m_DeathAnimation{}, 
            m_Speed{speed}, m_JumpHeight{jumpHeight}, m_SwitchTime{switchTime}, 
            m_CanJump{}, m_Health{100.f}, m_IsDead{}, m_SceneWidth{}, m_Cast{},

            m_Filename{filename}, m_ImgCount{imgCount}, m_Size{size}, m_Position{position}
    {
        Init(filename, imgCount, size, position, speed, jumpHeight, switchTime, sceneWidth);
    }


    Character::Character() 
        :   m_IdleAnimation{}, m_WalkingAnimation{}, m_JumpingAnimation{}, m_DeathAnimation{}, 
            m_Speed{}, m_JumpHeight{}, m_SwitchTime{}, 
            m_CanJump{}, m_Health{100.f}, m_IsDead{}, m_Cast{},

            m_Filename{}, m_ImgCount{}, m_Size{}, m_Position{}, m_SceneWidth{}
    {
    }


    void Character::Init(std::string const& filename, sf::Vector2u const& imgCount, sf::Vector2f const& size, sf::Vector2f const& position, 
                    float speed, float jumpHeight, float switchTime, uint sceneWidth)
    {
        m_Filename   = filename;
        m_ImgCount   = imgCount;
        m_Size       = size;
        m_Position   = position;
        m_Speed      = speed;
        m_JumpHeight = jumpHeight;
        m_SwitchTime = switchTime;
        m_SceneWidth = sceneWidth;

        // Loads a texture
        if (!s_Texture.loadFromFile(filename)) {
            fmt::print("Failed to load resource {}!", filename);
            std::abort();
        }

        m_Body.setSize(size);
        m_Body.setTexture(&s_Texture);
        m_Body.setPosition(position);
        m_Body.setOrigin(size / 2.f);
        
        m_Animator = std::make_shared<Animator>(s_Texture, imgCount, switchTime);
    }


    void Character::OnCollision(sf::Vector2f direction) {
        if (direction.x < 0.f)
            m_Velocity.x = 0.f;
        else if (direction.x > 0.f)
            m_Velocity.x = 0.f;

        if (direction.y < 0.f) {
            m_Velocity.y = 0.f;
            m_CanJump = true;
        }
        else if (direction.y > 0.f) {
            m_Velocity.y = 0.f;
        }
    }


    /*virtual*/ void Character::Update(float deltaTime) {    
        // If the character isn't dead
        if (m_Health > 0.f) {
            // Adds gravity to the character
            // 982.f is 9.82 m/s^2 converted (*= 100) as 100 pixels is 1m in our sfml coordinate space
            m_Velocity.y += 982.f * deltaTime;

            // If an animation should be played once
            if ((isValid(m_Cast) && !m_Cast->isCasting) || (!isValid(m_Cast))) {
                if (m_Velocity.x == 0.f)
                    m_Animator->SetIndecies(m_IdleAnimation);
                else
                    m_Animator->SetIndecies(m_WalkingAnimation);

                if (m_Velocity.y < 0.f)
                    m_Animator->SetIndecies(m_JumpingAnimation);
            }
            else if (isValid(m_Cast) && m_Cast->isCasting)
                m_Animator->SetIndecies(m_Cast->animation);
            
            uint const frame = m_Animator->Update(deltaTime);

            m_Body.setTextureRect(m_Animator->GetUVRect());
            m_Body.move(m_Velocity * deltaTime);

            // The final frame of the cast
            if (isValid(m_Cast) && frame == m_Cast->animation.size() - 1) {
                m_Cast->isCasting = false;
                m_Cast->isCasted = true;
            }

            // If the cast is valid
            if (isValid(m_Cast)) {
                // Positions the cast
                if (m_Cast->isCasting) {
			        m_Cast->isRight = m_Animator->IsFacingLeft();
                    m_Cast->cast.SetPosition({ m_Body.getPosition().x - (m_Cast->isRight ? 120.f : -120.f), m_Body.getPosition().y + 10.f });
                }
                // Moves the cast 
                else if (m_Cast->isCasted) {
                    m_Cast->cast.Move({ deltaTime * (m_Cast->isRight ? -1200.f : 1200.f), 0.f });
                    if (m_Cast->cast.GetPosition().x >= m_SceneWidth || m_Cast->cast.GetPosition().x <= 0) {
                        m_Cast->isCasted = false;
                        m_Cast = nullptr;
                    }
                }
            }
        }
        // If the character is dead
        else {
            m_Animator->SetIndecies(m_DeathAnimation);
            uint const frame = m_Animator->Update(deltaTime);
            m_Body.setTextureRect(m_Animator->GetUVRect());

            if (frame == m_DeathAnimation.size() - 1)
                m_IsDead = true;
        }
    }


    /*virtual*/ void Character::Draw(sf::RenderWindow& window) {
        if (isValid(m_Cast) && m_Cast->isCasted)
			m_Cast->cast.Draw(window);
	    
        window.draw(m_Body);
    }


    void Character::Hit(float damage) {
        m_Health -= damage;
    }


    void Character::RemoveCast() {
        m_Cast = nullptr;
    }


    void Character::SetIdle(std::vector<sf::Vector2u> const& animation) {
        m_IdleAnimation = animation;
    }


    void Character::SetWalking(std::vector<sf::Vector2u> const& animation) {
        m_WalkingAnimation = animation;
    }


    void Character::SetJumping(std::vector<sf::Vector2u> const& animation) {
        m_JumpingAnimation = animation;
    }


    void Character::SetDeath(std::vector<sf::Vector2u> const& animation) {
        m_DeathAnimation = animation;
    }


    void Character::SetVelocity(sf::Vector2f const& velocity) {
        m_Velocity = velocity;
    }


    void Character::SetFacingLeft(bool isFacingLeft) {
        m_Animator->SetFacing(isFacingLeft);
    }


    void Character::SetCast(Cast* const cast) {
        cast->isCasted = false;
        cast->isCasting = true;
        m_Cast = cast;
    }
}
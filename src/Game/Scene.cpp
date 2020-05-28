#include "Scene.hpp"
#include "../Logic/Validator.hpp"
#include "../Logic/Logger.hpp"
#include "../WindowManager.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


namespace Veri {
    Scene::Scene(std::string const& title, uint width) 
        :   m_Title{title}, m_Width{width}, m_Init{nullptr}, m_Loop{nullptr}, m_Backgrounds{} {}

    Scene::Scene()
        :   m_Title{}, m_Width{}, m_Init{nullptr}, m_Loop{nullptr}, m_Backgrounds{} {}


    Scene::Scene(Scene&& other) noexcept {
        if (&other != this) {
            m_Title         = std::move(other.m_Title);
            m_Width         = std::move(other.m_Width);
            m_Init          = std::move(other.m_Init);
            m_Loop          = std::move(other.m_Loop);
            m_Bounds        = std::move(other.m_Bounds);
            m_Player        = std::move(other.m_Player);
            m_Characters    = std::move(other.m_Characters);
            m_Backgrounds   = std::move(other.m_Backgrounds);
        }
    }


    Scene& Scene::operator=(Scene&& other) noexcept {
        if (&other != this) {
            m_Title         = std::move(other.m_Title);
            m_Width         = std::move(other.m_Width);
            m_Bounds        = std::move(other.m_Bounds);
            m_Player        = std::move(other.m_Player);
            m_Characters    = std::move(other.m_Characters);
            m_Backgrounds   = std::move(other.m_Backgrounds);
        }

        return *this;
    };


    void Scene::SetInit(std::function<void(void)> const& init) {
        m_Init = init;
    }


    void Scene::SetLoop(std::function<void(float)> const& loop) {
        m_Loop = loop;
    }


    void Scene::SetPlayer(std::shared_ptr<VeriPy::Player> player) {
        player->Create();
        m_Player = player;
    }


    void Scene::SetBackground(uint winWidth, std::string const& filename, sf::Vector2f const& origin) {        
        if (!s_Texture.loadFromFile(filename))
            Logger::Debug(Logger::Level::Critical, fmt::format("Failed to load resource {}!\n", filename), std::abort);
        
        uint amount = static_cast<std::size_t>(std::ceil(static_cast<float>(m_Width) / static_cast<float>(winWidth)));
        m_Backgrounds.reserve(amount);

        for (uint i = 0; i < amount; i++) {
            sf::Vector2f pos = { 0.f, 0.f };
            if (sf::Sprite const& prev = m_Backgrounds[i - 1]; i > 0)
                pos.x = prev.getPosition().x + s_Texture.getSize().x * prev.getScale().x;

            sf::Sprite sprite;
            sprite.setTexture(s_Texture, true);
            sprite.setPosition(pos);
            sprite.setOrigin(origin);
            sprite.setScale(s_Texture.getSize().x / winWidth * 1.1f, 1.f);
            
            m_Backgrounds.emplace_back(sprite);
        }
    }


    void Scene::AddBounds(Rectangle const& bounds) {
        m_Bounds.emplace_back(bounds);
    }


    void Scene::AddCharacter(std::pair<std::string, std::shared_ptr<VeriPy::Character>> character) {
        character.second->Create();
        m_Characters.emplace(character);
    }


    void Scene::RemoveCharacter(std::string const& name) {
        m_Characters.erase(name);
    }


    void Scene::AddRectangle(std::pair<std::string, std::shared_ptr<VeriPy::Rectangle>> rect) {
        rect.second->Create();
        m_Rectangles.emplace(rect);
    }


    void Scene::RemoveRectangle(std::string const& name) {
        m_Rectangles.erase(name);
    }


    void Scene::Run(float deltaTime, uint winWidth, sf::RenderWindow& window, Camera& camera) {
        valid(m_Loop)(deltaTime);
        
        sf::Vector2f direction = { 0.f, 0.f };        
        for (auto& border : m_Bounds) {
            for (auto&[key, character] : m_Characters) {
                if (border.GetCollider().CheckCollision(character->GetCharacter().GetCollider(), direction, 1.f))
                    character->GetCharacter().OnCollision(direction);

                if (border.GetCollider().CheckCollision(m_Player->GetPlayer()->GetCollider(), direction, 1.f))
                    m_Player->GetPlayer()->OnCollision(direction);

            }
        }

        // If the player is dead, remove him
        if (isValid(m_Player) && m_Player->GetPlayer()->IsDead())
            m_Player.reset();

        valid(m_Player)->GetPlayer()->Update(deltaTime);
        for (auto[key, val] : m_Characters)
            val->GetCharacter().Update(deltaTime);
            
        if (isValid(m_Player) && m_Player->GetPlayer()->GetPosition().x > winWidth / 2.f && m_Player->GetPlayer()->GetPosition().x + winWidth / 2.f < m_Width)
            camera.UpdateCenter({ m_Player->GetPlayer()->GetPosition().x, camera.GetCenter().y });

        window.setView(camera);
        for (auto const& background : m_Backgrounds)
            window.draw(background);

        // Draws the player
        valid(m_Player)->GetPlayer()->Draw(window);

        // Draws the rectangles
        for (auto&[key, val] : m_Characters)
            val->GetCharacter().Draw(window);
    
        for (auto&[key, val] : m_Rectangles)
            val->GetRectangle()->Draw(window);
    }
}
#pragma once

#include "../Graphics/Character.hpp"
#include "../VeriPy/Character.hpp"
#include "../VeriPy/Rectangle.hpp"
#include "../VeriPy/Player.hpp"
#include "../Game/Mage.hpp"
#include "../Graphics/Rectangle.hpp"
#include "../Graphics/Camera.hpp"
#include "../Logic/Logger.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>

namespace Veri {
    class Scene {
    public:
        Scene(std::string const& title, uint width);
        Scene();
        ~Scene() = default;

        Scene(Scene&& other) noexcept;
        Scene& operator=(Scene&& other) noexcept;

        void SetInit(std::function<void(void)> const& func);
        void SetLoop(std::function<void(float)> const& func);

        void SetPlayer(std::shared_ptr<VeriPy::Player> player);
        void SetBackground(uint winWidth, std::string const& filename, sf::Vector2f const& origin);

        void AddBounds(Rectangle const& bounds);
        
        void AddCharacter(std::pair<std::string, std::shared_ptr<VeriPy::Character>> character);
        void RemoveCharacter(std::string const& name);

        void AddRectangle(std::pair<std::string, std::shared_ptr<VeriPy::Rectangle>> rect);
        void RemoveRectangle(std::string const& name);

        void Run(float deltaTime, uint winWidth, sf::RenderWindow& window, Camera& camera);

        inline std::string                              GetTitle()       const { return m_Title;       }
        inline uint                                     GetWidth()       const { return m_Width;       }
        inline std::function<void(void)>  const&        GetInitializer() const { return m_Init;        }
        inline std::function<void(float)> const&        GetLooper()      const { return m_Loop;        }
        inline sf::Texture                              GetTexture()     const { return s_Texture;     }
        inline std::vector<sf::Sprite>                  GetBackgrounds() const { return m_Backgrounds; }
        
        inline std::shared_ptr<VeriPy::Character> GetCharacters(std::string const& name) const { 
            if (auto where = m_Characters.find(name); where != std::end(m_Characters))
                return where->second;

            return nullptr;
        }


        inline std::shared_ptr<VeriPy::Rectangle> GetRectangles(std::string const& name) const { 
            if (auto where = m_Rectangles.find(name); where != std::end(m_Rectangles))
                return where->second;

            return nullptr;
        }

        inline std::shared_ptr<VeriPy::Player> GetPlayer() {
            return m_Player;
        }
        
    private:
        std::string m_Title;
        uint m_Width;

        std::function<void(void)> m_Init;
        std::function<void(float)> m_Loop;

        std::vector<Rectangle> m_Bounds;
        std::vector<sf::Sprite> m_Backgrounds{};

        std::shared_ptr<VeriPy::Player> m_Player;
        std::unordered_map<std::string, std::shared_ptr<VeriPy::Character>> m_Characters;
        std::unordered_map<std::string, std::shared_ptr<VeriPy::Rectangle>> m_Rectangles;
        
        static inline sf::Texture s_Texture{};
    };
}
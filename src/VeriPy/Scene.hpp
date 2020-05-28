#pragma once

#include "../WindowManager.hpp"
#include "../Game/SceneManager.hpp"
#include "../Logic/Logger.hpp"
#include "Player.hpp"
#include <string>
#include <functional>
#include <tuple>


namespace VeriPy {
    class Scene {
    public:
        Scene(std::string const& title, uint width);
        ~Scene() = default;

        void Init(std::function<void(void)> const& func);
        void Loop(std::function<void(float)> const& func);
        void Quit();

        void SetBackground(std::string const& filename, std::pair<float, float> origin);
        void SetPlayer(Player const& player);
        void PlayerFaceLeft(bool isFacingLeft);

        void AddBounds(float x, float y, float w, float h);
        void AddCharacter(std::string const& name, Character const& character);
        void AddRectangle(std::string const& name, Rectangle const& rectangle);

        void RemoveRectangle(std::string const& name);
        void RemoveCharacter(std::string const& name);

        std::string const& GetTitle() const;
        uint GetWidth() const;

        std::shared_ptr<Character> GetCharacter(std::string const& name);
        std::shared_ptr<Rectangle> GetRectangle(std::string const& name);
        std::shared_ptr<Player> GetPlayer();

    private:
        std::string m_Title;
        uint m_Width;
    };
}
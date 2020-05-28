#include "WindowManager.hpp"
#include "imgui/imgui.h"

namespace {
    sf::RenderWindow s_Window{};
}

namespace Veri {
    // Creates a window
    sf::RenderWindow& WindowMananger::CreateWindow(sf::VideoMode const& mode, std::string const& title) {
        s_Window.create(mode, title);
        s_Window.setKeyRepeatEnabled(false);

        return s_Window;
    }


    // Gets the window
    sf::RenderWindow& WindowMananger::GetWindow() {
        return s_Window;
    }
}
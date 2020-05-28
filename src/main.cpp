#include <fstream>                          // std::ifstream
#include <optional>                         // std::optional
#include <string>                           // std::string
#include <memory>                           // std::shared_ptr

#include "Logic/Event/Event.hpp"            // Veri::Event
#include "Logic/Event/EventManager.hpp"     // Veri::EventManager
#include "Logic/Event/WinEvent.hpp"         // Veri::Event::WinEvent
#include "Logic/Event/KbEvent.hpp"          // Veri::Event::KbEvent

#include "Game/SceneManager.hpp"            // Veri::SceneManager
#include "Game/Scene.hpp"                   // Veri::Scene

#include "Logic/Filesystem.hpp"             // Filesystem
#include "Logic/Timer.hpp"                  // Veri::Logger

#include "Logic/Logger.hpp"                 // Veri::Logger
#include "WindowManager.hpp"                // Veri::WindowManager

#include "pybind11/embed.h"                 // pybind11::embed
#include "pybind11/pybind11.h"              // pybind11
#include "imgui/imgui.h"                    // ImGUI
#include "imgui/imgui-SFML.h"               // ImGUI-SFML

// Defines a macro for Debug and Release mode
#define MODE_DEBUG "Debug"
#define MODE_RELEASE "Release"

// Checks which mode it's compiled for
#ifdef RPG_DEBUG
    constexpr std::string_view MODE = MODE_DEBUG;
#elif RPG_RELEASE
    constexpr std::string_view MODE = MODE_RELEASE;
#endif


// Parses a regular file
std::optional<std::string> PythonParser(std::string const& filename) {
    std::ifstream reader(filename.c_str());
    if (reader) {
        std::string out{};
        std::string line{};

        while(std::getline(reader, line))
            out += line + '\n';
    
        return out;
    }

    return {};
}

// Some aliases
namespace Py = pybind11;
namespace Wm = Veri::WindowMananger;
using Em = Veri::EventManager;

int main() {
    // Initialize the logger with MODE (either Debug or Release)
    Veri::Logger::Init("dev", MODE_DEBUG, "RPG");    
    Veri::Logger::Debug(Veri::Logger::Level::Info, fmt::format("Starting Game in {} mode\n", MODE_DEBUG));

    // Window width and height
    constexpr uint WIN_WIDTH = 1920;
    constexpr uint WIN_HEIGHT = 1080;

    // Creates the window
	auto& window = Veri::WindowMananger::CreateWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "RPG");
    ImGui::SFML::Init(window, false);

    // Adds a window-closed event
    Em::GetInstance().AddEvent(Veri::WinEvent::MakeEvent(Veri::Type::Closed, [&window]{ 
        Veri::Timer::Sleep(Veri::Timer::MilliSeconds(500));
        window.close();
    }));

    // Python interpreter
    Py::scoped_interpreter guard{};
    Veri::Logger::Debug(Veri::Logger::Level::Info, "Parsing python-scene file!");

    // Tries to parse the file into a string
    auto script = PythonParser(FindFile("../src/Game/Scenes/scene_hub.py"));
    if (!script.has_value() || script.value().empty()) {
        Veri::Logger::Log(Veri::Logger::Level::Critical, "Couldn't run script scene_hub.py!");
        std::abort();
    }

    // Executes the file
    Py::exec(script.value());

    // Gets the scene into a variable
    std::shared_ptr<Veri::Scene> hubScene = Veri::SceneManager::GetScene("Hub");
    if (hubScene == nullptr) {
        Veri::Logger::Debug(Veri::Logger::Level::Critical, "hubScene was nullptr!\n", std::abort);
        std::abort();
    }

    // Invokes the python script's init
    std::invoke(hubScene->GetInitializer());

    // Creates the camera
    sf::Vector2f cameraCenter = { Wm::GetWindow().getSize().x / 2.f, 0.f };
    if (!hubScene->GetBackgrounds().empty())
        cameraCenter.y = hubScene->GetTexture().getSize().y - Wm::GetWindow().getSize().y / 2.f - hubScene->GetBackgrounds()[0].getOrigin().y;
    
    sf::Vector2f cameraSize = { static_cast<float>(Wm::GetWindow().getSize().x), static_cast<float>(Wm::GetWindow().getSize().y) };
    Veri::Camera camera(cameraCenter, cameraSize, Wm::GetWindow().getSize().y);

    // Tick
    float deltaTime{};
    sf::Clock clock{};

    // Game loop
    while (window.isOpen()) {
        // Updates the tick
        sf::Time time = clock.restart();
        deltaTime = time.asSeconds();
        ImGui::SFML::Update(window, time);
        
		// 60 tick-rate
        if (deltaTime >= 1.f / 60.f)
            deltaTime = 1.f / 60.f;

        Veri::EventManager::GetInstance().PollEvents(window);

        window.clear();
        hubScene->Run(deltaTime, WIN_WIDTH, window, camera);
        
        // Renders all imgui-based widgets   
        ImGui::SFML::Render(window);
        
        window.display();
    }

    ImGui::SFML::Shutdown();

    Veri::SceneManager::DestroyScene(hubScene);
    Veri::Logger::Debug(Veri::Logger::Level::Info, "Quitting game");
}
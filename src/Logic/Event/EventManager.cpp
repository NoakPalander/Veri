#include "EventManager.hpp"
#include "fmt/fmt.hpp"
#include "imgui/imgui-SFML.h"


namespace Veri {
    void EventManager::AddEvent(std::shared_ptr<Event> evntPtr) {
        // The key already exists, append it to the vector
        if (auto where = m_Events.find(evntPtr->GetType()); where != std::end(m_Events))
            where->second.emplace_back(evntPtr);
        // otherwise add another keybind to it
        else
            m_Events.emplace(evntPtr->GetType(), std::vector<std::shared_ptr<Event>>{ evntPtr });
    }

    // Removes the event by value (ptr)
    void EventManager::RemoveEvent(std::shared_ptr<Event> evntPtr) {
        if (evntPtr) {
            auto& vec = m_Events[evntPtr->GetType()];
            if (!vec.empty())
                if (auto where = std::find(std::begin(vec), std::end(vec), evntPtr); where != std::end(vec))
                    vec.erase(where);   
        }
    }


    // Possibly very slow memory leak? Requires investigation
    void EventManager::PollEvents(sf::RenderWindow& window) {
        static sf::Event e;
        while (window.pollEvent(e)) {
            ImGui::SFML::ProcessEvent(e);
            for (auto event : m_Events[e.type])
                event->OnEvent(e);
        }
    }


    // Gets a thread-safe instance
    /*static*/ EventManager& EventManager::GetInstance() {
        static EventManager s_Manager{};
        return s_Manager;
    }
}
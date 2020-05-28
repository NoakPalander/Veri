#include "Scene.hpp"
#include "../Logic/Filesystem.hpp"


namespace VeriPy {
    Scene::Scene(std::string const& title, uint width) 
        :   m_Title{title}, m_Width{width} {

        Veri::SceneManager::CreateScene(title, width);
    }
    

    void Scene::Init(std::function<void(void)> const& func) {
        Veri::SceneManager::GetScene(m_Title)->SetInit(func);
    }


    void Scene::Quit() {
        Veri::Timer::Sleep(Veri::Timer::MilliSeconds(500));
        Veri::WindowMananger::GetWindow().close();
    }


    void Scene::Loop(std::function<void(float)> const& func) {
        Veri::SceneManager::GetScene(m_Title)->SetLoop(func);
    }


    void Scene::SetBackground(std::string const& filename, std::pair<float, float> origin) {
        Veri::SceneManager::GetScene(m_Title)->SetBackground(Veri::WindowMananger::GetWindow().getSize().x, filename, 
            { origin.first, origin.second });
    }


    void Scene::SetPlayer(Player const& player) {
        Veri::SceneManager::GetScene(m_Title)->SetPlayer(std::make_shared<VeriPy::Player>(player));
    }


    void Scene::AddBounds(float x, float y, float w, float h) {
        Veri::SceneManager::GetScene(m_Title)->AddBounds(Veri::Rectangle{ { w, h }, { x, y }});
    }


    void Scene::AddCharacter(std::string const& name, Character const& character) {
        Veri::SceneManager::GetScene(m_Title)->AddCharacter(std::make_pair(name, std::make_shared<Character>(character)));
    }


    void Scene::AddRectangle(std::string const& name, Rectangle const& rectangle) {
        Veri::SceneManager::GetScene(m_Title)->AddRectangle(std::make_pair(name, std::make_shared<Rectangle>(rectangle)));
    }


    void Scene::RemoveRectangle(std::string const& name) {
        Veri::SceneManager::GetScene(m_Title)->RemoveRectangle(name);
    }
    
    
    void Scene::RemoveCharacter(std::string const& name) {
        Veri::SceneManager::GetScene(m_Title)->RemoveCharacter(name);
    }


    std::string const& Scene::GetTitle() const {
        return m_Title; 
    }


    uint Scene::GetWidth() const {
        return m_Width; 
    }


    std::shared_ptr<Character> Scene::GetCharacter(std::string const& name) {
        return Veri::SceneManager::GetScene(m_Title)->GetCharacters(name);
    }


    std::shared_ptr<Rectangle> Scene::GetRectangle(std::string const& name) {
        return Veri::SceneManager::GetScene(m_Title)->GetRectangles(name);
    }


    std::shared_ptr<Player> Scene::GetPlayer() {
        return Veri::SceneManager::GetScene(m_Title)->GetPlayer();
    }
}